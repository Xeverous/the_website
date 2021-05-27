"""
based on:
https://docutils.sourceforge.io/docs/howto/rst-directives.html
https://docutils.sourceforge.io/docs/howto/rst-roles.html
https://github.com/getnikola/nikola/blob/master/nikola/plugins/compile/rest/media.py
https://github.com/getnikola/nikola/issues/3415
more examples:
https://stackoverflow.com/questions/16719826/nesting-sphinx-extension-directives-with-rest
https://github.com/fabpot/sphinx-php/blob/master/sensio/sphinx/configurationblock.py
"""

from docutils import nodes
from docutils.parsers.rst import Directive, directives, roles

from nikola.plugin_categories import RestExtension
from nikola.utils import get_logger

from typing import List, Dict, Optional

import os
import sys

try:
    # THIS IS BAD but works whenever ACH is rebuilt
    sys.path.append(os.path.abspath(os.path.dirname(__file__)) +
        "/../external/arbitrary_code_highlighter/build/lib")
    import pyach
except ImportError:
    pyach = None

VALID_CSS_CLASSES = ("built_in;keyword;type;namespace;enum;const;ext;func;oo;suf;label;"
"var_local;var_member;var_static;param;mparam;tparam;concept;problem;num;str;str_esc;chr;chr_esc;"
"com_single;com_multi;com_tag;com_single_dox;com_multi_dox;com_tag_dox;pp_direct;pp_header;pp_other;"
"macro_def;macro_ref;asm_direct")

DATA_FILES_PATH = "data"
INLINE_CODES_CODE_PATH = DATA_FILES_PATH + "/inline_codes.cpp"
INLINE_CODES_COLOR_PATH = DATA_FILES_PATH + "/inline_codes.color"

class RestHighlighter(RestExtension):
    """Plugin for custom reST directive."""

    name = "rest_highlighter"

    def set_site(self, site):
        self.site = site

        logger = get_logger(__name__)
        if pyach:
            logger.info(f"using ACH version {'.'.join(str(i) for i in pyach.version())}")
            inline_codes = load_inline_codes()
            logger.info(f"loaded inline codes: {len(inline_codes)} lines")
        else:
            logger.error("failed to import ACH extension, reST extensions will generate dummy output")
            inline_codes = None

        # custom directives need to register a class that implements certain members
        # custom roles need to register a function - because we need to pass some state
        # to the function we pass a class instance that has implemented __call__ instead
        directives.register_directive('cch', CustomCodeHighlight)
        roles.register_local_role('cch', CustomCodeHighlightInline(inline_codes))

        return super().set_site(site)

def load_inline_codes() -> Dict[str, str]:
    code_lines = read_file_split_lines(INLINE_CODES_CODE_PATH)
    color_lines = read_file_split_lines(INLINE_CODES_COLOR_PATH)

    if (len(code_lines) != len(color_lines)):
        raise RuntimeError(f"inline code sources differ, "
            f"code has {len(code_lines)} lines "
            f"but color has {len(color_lines)}")

    result = {}
    logger = get_logger(__name__)
    for i, (code, color) in enumerate(zip(code_lines, color_lines), 1):
        try:
            if result.get(code):
                logger.error(f'duplicate inline code defined: "{code}"')
            highlighted = pyach.run_highlighter(code, color,
                replace=True, valid_css_classes=VALID_CSS_CLASSES)
            result[code] = f'<code class="code custom-cpp">{highlighted}</code>'
        except RuntimeError as err:
            logger.error(f'inline code line {i}: highlight failed:\n{str(err)}')

    return result

class CustomCodeHighlightInline:
    def __init__(self, inline_codes: Optional[Dict[str, str]]):
        self.inline_codes = inline_codes

    def __call__(self, name, rawtext, text, lineno, inliner, options={}, content=[]):
        if not self.inline_codes:
            # fail gracefully with dummy output, do not report errors
            # they are already reported when plugin fails to initialize
            result = "<em>ERROR WHILE INITIALIZING INLINE ACH; OUTPUT WOULD BE HERE</em>"
            msg = []
            return [nodes.raw('', result, format='html')], msg

        html_output = self.inline_codes.get(text)
        if html_output is None:
            msg = inliner.reporter.error(f'code "{text}" was not found in inline codes', line=lineno)
            prb = inliner.problematic(rawtext, rawtext, msg)
            return [prb], [msg]

        return [nodes.raw('', html_output, format='html')], []

class CustomCodeHighlight(Directive):
    has_content = False
    required_arguments = 0
    optional_arguments = 0
    option_spec = {
        'code_path': directives.path,
        'color_path': directives.path,
        'lang': directives.unchanged,
    }

    def run(self):
        if pyach is None:
            result = "<em>ERROR WHILE LOADING ACH; OUTPUT WOULD BE HERE</em>"
            return [nodes.raw('', result, format='html')]

        code_path = self.options["code_path"]
        color_path = self.options["color_path"]
        is_code_path_relative = is_relative_path(code_path)
        is_color_path_relative = is_relative_path(color_path)
        rst_source_path = self.state.document.settings._nikola_source_path

        if is_code_path_relative != is_color_path_relative:
            logger = get_logger(__name__)
            logger.warn(f'{rst_code_path} called CCH extension with inconsistent paths: '
                f'{code_path} is {make_not_word(is_code_path_relative)} relative but '
                f'{color_path} is {make_not_word(is_color_path_relative)} relative')

        lang = self.options.get("lang")
        if not lang:
            lang = "custom-cpp"

        code_path = make_path(rst_source_path, code_path)
        color_path = make_path(rst_source_path, color_path)

        code_str = read_file(code_path)
        color_str = read_file(color_path)

        try:
            result = pyach.run_highlighter(code_str, color_str, table_wrap_css_class=lang,
                replace=True, valid_css_classes=VALID_CSS_CLASSES)
        except RuntimeError as err:
            raise self.error(f'highlight failed:\n{str(err)}\n'
                f'code_path: {code_path}\n'
                f'color_path: {color_path}\n'
                f'valid_css_classes: {VALID_CSS_CLASSES}\n')

        # report dependency on used files - required to support incremental build
        self.state.document.settings.record_dependencies.add(code_path)
        self.state.document.settings.record_dependencies.add(color_path)

        return [nodes.raw('', result, format='html')]

def is_relative_path(path: str) -> bool:
    return path[0] != "/"

def make_not_word(b: bool) -> str:
    if b:
        return ""
    else:
        return "not "

def make_path(rst_source_path: str, path: str) -> str:
    if is_relative_path(path):
        return os.path.join(os.path.dirname(rst_source_path), path)
    else:
        return path

def read_file(path: str) -> str:
    with open(path, 'r', encoding="utf-8") as file:
        return file.read()

def read_file_split_lines(path: str) -> List[str]:
    return read_file(path).splitlines()
