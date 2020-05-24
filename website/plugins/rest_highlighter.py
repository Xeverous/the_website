"""
based on:
https://docutils.sourceforge.io/docs/howto/rst-directives.html
https://github.com/getnikola/nikola/blob/master/nikola/plugins/compile/rest/media.py
https://github.com/getnikola/nikola/issues/3415
"""

from docutils import nodes
from docutils.parsers.rst import Directive, directives

from nikola.plugin_categories import RestExtension
from nikola.utils import get_logger

import os
import sys

try:
    # THIS IS BAD but works whenever ACH is rebuilt
    sys.path.append(os.path.abspath(os.path.dirname(__file__)) +
        "/../external/arbitrary_code_highlighter/build/lib")
    import pyach
except ImportError:
    pyach = None

class RestHighlighter(RestExtension):
    """Plugin for custom reST directive."""

    name = "rest_highlighter"

    def set_site(self, site):
        self.site = site
        directives.register_directive('cch', CustomCodeHighlight)

        logger = get_logger(__name__)
        if pyach:
            logger.info(f"using ACH version {'.'.join(str(i) for i in pyach.version())}")
        else:
            logger.warn("failed to import ACH extension, reST extensions will generate dummy output")

        return super().set_site(site)


class CustomCodeHighlight(Directive):
    # RST extension data
    has_content = False
    required_arguments = 0
    optional_arguments = 0
    option_spec = {
        'code_path': directives.path,
        'color_path': directives.path,
        'lang': directives.unchanged,
    }

    # our data
    valid_css_classes = ("built_in;keyword;type;namespace;enum;const;ext;func;oo;suf;label;"
    "var_local;var_member;var_static;param;mparam;tparam;concept;problem;num;str;str_esc;chr;chr_esc;"
    "com_single;com_multi;com_tag;com_single_dox;com_multi_dox;com_tag_dox;pp_direct;pp_header;pp_other;"
    "macro_def;macro_ref;asm_direct")

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

        if "lang" in self.options:
            lang = self.options["lang"]
        else:
            lang = "custom-cpp"

        code_path = make_path(rst_source_path, code_path)
        color_path = make_path(rst_source_path, color_path)

        code_str = read_file(code_path)
        color_str = read_file(color_path)

        try:
            result = pyach.run_highlighter(code_str, color_str, table_wrap_css_class = lang, replace = True,
                valid_css_classes = self.valid_css_classes)
        except RuntimeError as err:
            raise self.error(f'highlight failed:\n{str(err)}\n'
                f'code_path: {code_path}\n'
                f'color_path: {color_path}\n'
                f'valid_css_classes: {self.valid_css_classes}\n')

        # report dependency on content of used files
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
        return os.path.dirname(rst_source_path) + "/" + path
    else:
        return path

def read_file(path: str) -> str:
    with open(path, 'r', encoding="utf-8") as file:
        return file.read()
