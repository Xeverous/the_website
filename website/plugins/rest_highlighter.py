"""
based on:
https://docutils.sourceforge.io/docs/howto/rst-directives.html
https://docutils.sourceforge.io/docs/howto/rst-roles.html
https://github.com/getnikola/nikola/blob/master/nikola/plugins/compile/rest/media.py
https://github.com/getnikola/nikola/issues/3415
more examples:
https://stackoverflow.com/questions/16719826/nesting-sphinx-extension-directives-with-rest
https://github.com/fabpot/sphinx-php/blob/master/sensio/sphinx/configurationblock.py

"cch" role and directive use arbitrary_code_highlighter (cutom implementation)
"ansi" directive uses ansi2html library to convert ASNI-escaped text to HTML
"""

from docutils import nodes
from docutils.parsers.rst import Directive, directives, roles

from nikola.plugin_categories import RestExtension
from nikola.utils import get_logger

from plugins.file_utils import is_relative_path, make_path_absolute, path_description, read_file

from typing import Any, Dict, Optional

import os
import sys

try:
    # THIS IS BAD but works whenever ACH is rebuilt
    sys.path.append(os.path.abspath(os.path.dirname(__file__)) +
        "/../external/arbitrary_code_highlighter/build/lib")
    import pyach
except ImportError as err:
    get_logger(__name__).error(f"failed to import ACH: {str(err)}")
    pyach = None

import ansi2html
import pkg_resources

from plugins.html_utils import escape_text_into_html
from plugins.clangd import Clangd

##############################################################################
# utilities
##############################################################################

def enclose_in_html(text: str, html_tag: str, css_classes: Optional[str] = None) -> str:
    if css_classes:
        return f'<{html_tag} class="{css_classes}">{text}</{html_tag}>'
    else:
        return f'<{html_tag}>{text}</{html_tag}>'

def bytes_to_hex_string(bytes: bytearray) -> str:
    return ', '.join('0x{:02x}'.format(x) for x in bytes)

##############################################################################
# common code
##############################################################################

class RestHighlighter(RestExtension):
    """Plugin for custom reST directives and roles."""

    name = "rest_highlighter"

    def set_site(self, site):
        self.site = site

        logger = get_logger(__name__)
        if pyach:
            logger.info(f"using ACH version {'.'.join(str(i) for i in pyach.version())}")
            inline_codes = load_inline_codes()
            logger.info(f"loaded inline codes: {len(inline_codes)} lines")
        else:
            logger.error("failed to import ACH extension, cch roles and directives will generate dummy output")
            inline_codes = None
        logger.info(f"using ansi2html version {pkg_resources.get_distribution('ansi2html').version}")

        # custom directives need to register a class that implements certain members
        # custom roles need to register a function - because we need to pass some state
        # to the function we pass a class instance that has implemented __call__ instead
        directives.register_directive('cch', CustomCodeHighlight)
        roles.register_local_role('cch', CustomCodeHighlightInline(inline_codes))
        directives.register_directive('ansi', AnsiHighlight)

        return super().set_site(site)

##############################################################################
# CCH implementation
##############################################################################

VALID_CSS_CLASSES = ("keyword;type;namespace;enum;ext;func;oo;concept;problem;label;spec;"
"var_local;var_member;var_global;param;param_out;param_tmpl;lit_pre;lit_suf;lit_num;lit_str;lit_chr;esc_seq;fmt_seq;"
"com_single;com_multi;com_tag_todo;com_single_dox;com_multi_dox;com_tag_dox;pp_hash;pp_directive;pp_header;pp_other;"
"macro;pp_macro;pp_macro_param;pp_macro_body;asm_direct")

DATA_FILES_PATH = "data"
KEYWORDS_PATH = DATA_FILES_PATH + "/keywords.txt"
HEADERS_PATH = DATA_FILES_PATH + "/headers.txt"
INLINE_CODES_CODE_PATH = DATA_FILES_PATH + "/inline_codes.cpp"
INLINE_CODES_COLOR_PATH = DATA_FILES_PATH + "/inline_codes.color"
KEYWORDS_LIST = read_file(KEYWORDS_PATH).splitlines()

def run_mirror_highlighter_inline(code: str, color: str) -> str:
    highlighted = pyach.run_mirror_highlighter(code, color,
        replace=True, valid_css_classes=VALID_CSS_CLASSES)
    return enclose_in_html(highlighted, "code", "code custom-cpp")

def inline_codes_add_entry(inline_codes: Dict[str, str], code: str, color: str, line: int):
    logger = get_logger(__name__)
    try:
        if inline_codes.get(code):
            logger.error(f'duplicate inline code defined: "{code}"')
        inline_codes[code] = run_mirror_highlighter_inline(code, color)
    except RuntimeError as err:
        logger.error(f'inline code highlight failed [line = {line}]:\n{str(err)}')

def load_inline_codes() -> Dict[str, str]:
    headers = read_file(HEADERS_PATH).splitlines()
    code_lines = read_file(INLINE_CODES_CODE_PATH).splitlines()
    color_lines = read_file(INLINE_CODES_COLOR_PATH).splitlines()

    if (len(code_lines) != len(color_lines)):
        raise RuntimeError(f"inline code sources differ, "
            f"code has {len(code_lines)} lines "
            f"but color has {len(color_lines)}")

    result = {}

    for i, code in enumerate(KEYWORDS_LIST, 1):
        inline_codes_add_entry(result, code, "keyword", i)

    for i, code in enumerate(headers, 1):
        inline_codes_add_entry(result, code, "0pp_header", i)

    for i, code in enumerate(headers, 1):
        inline_codes_add_entry(result, f"#include {code}", "1pp_hash`pp_directive 0pp_header", i)

    for i, (code, color) in enumerate(zip(code_lines, color_lines), 1):
        inline_codes_add_entry(result, code, color, i)

    # workaround for some totally obscure bug, probably within docutils
    # problem: some inline directives with backslashes are incorrectly parsed,
    # they contain additional null characters for no reason
    # example: :directive:`'\0'`    gives ["'", "\0", "0", "'"]
    # example: :directive:`'\\0'`   gives ["'", "\0", "\\", "0", "'"]
    # example: :directive:`'\\\0'`  gives ["'", "\0", "\\", "\0", "0", "'"]
    # example: :directive:`'\\\\0'` gives ["'", "\0", "\\", "\0", "\\" ,"0", "'"]
    # right now there are only few affected strings so just adding their corrupted versions
    # as a copies of the proper ones
    result["\0\\0"] = result.get("\\0")
    result["\0\\n"] = result.get("\\n")
    result["\0\\r"] = result.get("\\r")
    result["'\0\\0'"] = result.get("'\\0'")
    result["'\0\\n'"] = result.get("'\\n'")
    result["'\0\\r'"] = result.get("'\\r'")

    return result

class CustomCodeHighlightInline:
    # inline_codes should be already a mapping of code strings to output strings
    def __init__(self, inline_codes: Optional[Dict[str, str]]):
        self.inline_codes = inline_codes

    def __call__(self, name, rawtext, text, lineno, inliner, options={}, content=[]):
        if not self.inline_codes:
            # fail gracefully with raw text
            # problems are already reported when the plugin fails to initialize
            result = enclose_in_html(escape_text_into_html(text), "code")
            return [nodes.raw('', result, format='html')], []

        # inline code with explicit color specification
        if "$$$" in text:
            l = text.split("$$$")
            if len(l) != 2:
                msg = inliner.reporter.error(
                    f'code "{text}" should contain exactly one $$$ token', line=lineno)
                prb = inliner.problematic(rawtext, rawtext, msg)
                return [prb], [msg]
            try:
                html_output = run_mirror_highlighter_inline(l[0], l[1])
                return [nodes.raw('', html_output, format='html')], []
            except RuntimeError as err:
                get_logger(__name__).error(f'inline code with $$$: highlight failed:\n{str(err)}')
                msg = inliner.reporter.error(
                    f'inline code "{text}" failed to highlight', line=lineno)
                prb = inliner.problematic(rawtext, rawtext, msg)
                return [prb], [msg]

        html_output = self.inline_codes.get(text)
        if html_output is None:
            error_str = f'code "{text}" was not found in inline codes'
            # for unknown reason, some directives are reported with additional, unwanted null characters
            # this helps identify such cases by printing the string as an array of hex
            if "\0" in text:
                error_str += f'; code = [{bytes_to_hex_string(bytearray(text, "utf-8"))}]'
            msg = inliner.reporter.error(error_str, line=lineno)
            prb = inliner.problematic(rawtext, rawtext, msg)
            return [prb], [msg]
        return [nodes.raw('', html_output, format='html')], []

# Docutils directives.unchanged actually changes None into ""
def passthrough(value: Any) -> Any:
    return value

def fail_gracefully(result: str, css_class: str = "code"):
    result = enclose_in_html(result, "pre", css_class)
    return [nodes.raw('', result, format='html')]

class CustomCodeHighlight(Directive):
    # required by docutils
    has_content = False
    required_arguments = 0
    optional_arguments = 0
    option_spec = {
        "code_path": directives.unchanged_required,
        "color_path": passthrough,
        "lang": passthrough,
    }

    # for internal purposes
    clangd = Clangd()

    def run(self):
        code_path = self.options["code_path"]
        color_path = self.options.get("color_path")
        rst_source_path = self.state.document.settings._nikola_source_path
        code_absolute_path = make_path_absolute(rst_source_path, code_path)
        # report dependency on used files - required to support incremental build
        self.state.document.settings.record_dependencies.add(code_absolute_path)

        if not color_path:
            return self.run_clangd_highlighter(code_absolute_path)

        is_code_path_relative = is_relative_path(code_path)
        is_color_path_relative = is_relative_path(color_path)

        if is_code_path_relative != is_color_path_relative:
            get_logger(__name__).warn(f"{rst_source_path} called CCH extension with inconsistent paths: "
                f"{code_path} is {path_description(is_code_path_relative)} but "
                f"{color_path} is {path_description(is_color_path_relative)}")

        color_absolute_path = make_path_absolute(rst_source_path, color_path)
        self.state.document.settings.record_dependencies.add(color_absolute_path)
        lang = self.options.get("lang", "custom-cpp")
        return self.run_mirror_highlighter(code_absolute_path, color_absolute_path, lang)

    def run_mirror_highlighter(self, code_absolute_path: str, color_absolute_path: str, lang: str):
        try:
            code_str = read_file(code_absolute_path)
            color_str = read_file(color_absolute_path)

            if pyach is None:
                # fail gracefully with raw text
                # problems are already reported when the plugin fails to initialize
                return fail_gracefully(code_str, f"code {lang}")

            result = pyach.run_mirror_highlighter(code_str, color_str, table_wrap_css_class=lang,
                replace=True, valid_css_classes=VALID_CSS_CLASSES)
            return [nodes.raw('', result, format='html')]
        except Exception as err:
            # Log and return error_str instead of raise self.error(error_str) because
            # either way, error_str will land on the page.
            # If it's done through exception, it's not formatted well and hard to read.
            error_str = (f'mirror highlight failed:\n{str(err)}'
                f'code_path: {code_absolute_path}\n'
                f'color_path: {color_absolute_path}\n'
                f'valid_css_classes: {VALID_CSS_CLASSES}')
            get_logger(__name__).error(error_str)
            return fail_gracefully(error_str)

    def run_clangd_highlighter(self, code_absolute_path: str):
        try:
            lang = "custom-cpp"

            if pyach is None:
                # fail gracefully with raw text
                # problems are already reported when the plugin fails to initialize
                return fail_gracefully(read_file(code_absolute_path), f"code {lang}")

            file_content, semantic_tokens = CustomCodeHighlight.clangd.file_content_and_semantic_tokens_with_color_variance(code_absolute_path)
            result = pyach.run_clangd_highlighter(
                file_content,
                semantic_token_types=CustomCodeHighlight.clangd.semantic_token_types,
                semantic_token_modifiers=CustomCodeHighlight.clangd.semantic_token_modifiers,
                semantic_tokens=semantic_tokens,
                keywords=KEYWORDS_LIST,
                table_wrap_css_class=lang)
            return [nodes.raw('', result, format='html')]
        except Exception as err:
            error_str = (f"clangd highlight failed:\n{str(err)}\ncode_path: {code_absolute_path}\n")
            get_logger(__name__).error(error_str)
            return fail_gracefully(error_str)


##############################################################################
# ANSI implementation
##############################################################################

class AnsiHighlight(Directive):
    # required by docutils
    has_content = False
    required_arguments = 0
    optional_arguments = 0
    option_spec = {
        'ansi_path': directives.path,
    }

    # for internal purposes
    converter = ansi2html.Ansi2HTMLConverter(line_wrap=False)

    def run(self):
        ansi_path = self.options["ansi_path"]
        rst_source_path = self.state.document.settings._nikola_source_path
        ansi_path = make_path_absolute(rst_source_path, ansi_path)

        try:
            # full=False disables HTML preamble - we want only <span> elements
            result = enclose_in_html(
                AnsiHighlight.converter.convert(read_file(ansi_path), full=False),
                "pre",
                "code ansi")
        except Exception as err:
            raise self.error(f'highlight failed:\n{str(err)}\nansi_path: {ansi_path}\n')

        # report dependency on used files - required to support incremental build
        self.state.document.settings.record_dependencies.add(ansi_path)

        return [nodes.raw('', result, format='html')]
