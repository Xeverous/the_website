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

class RestHighlighter(RestExtension):
    """Plugin for custom reST directive."""

    name = "rest_media"

    def set_site(self, site):
        self.site = site
        directives.register_directive('cch', CustomCodeHighlight)
        return super().set_site(site)


class CustomCodeHighlight(Directive):
    has_content = False
    required_arguments = 0
    optional_arguments = 0
    option_spec = {
        'source_path': directives.path,
        'color_path': directives.path
    }

    def run(self):
        logger = get_logger(__name__)
        logger.info('Called CCH with source_path = "{source_path}" and color_path = "{color_path}"'.format(**self.options))
        logger.info(f'page path: {self.state.document.settings._nikola_source_path}')

        result = "<em>CCH OUTPUT HERE</em>"
        return [nodes.raw('', result, format='html')]
