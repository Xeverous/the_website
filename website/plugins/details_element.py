from docutils import nodes
from docutils.parsers.rst import Directive, directives

from nikola.plugin_categories import RestExtension
from nikola.utils import get_logger

from plugins.html_utils import escape_text_into_html

class DetailsElement(RestExtension):
    """Plugin for custom reST directive that outputs HTML <details> element."""

    name = "details_element"

    def set_site(self, site):
        self.site = site
        directives.register_directive('details', DetailsDirective)
        return super().set_site(site)

class DetailsDirective(Directive):
    has_content = True
    required_arguments = 0
    optional_arguments = 0
    option_spec = {
        'open': directives.flag,
        'summary': directives.unchanged_required
    }

    def run(self):
        self.assert_has_content()

        summary_text = escape_text_into_html(self.options["summary"])
        opening_tag = f"<details><summary>{summary_text}</summary>"
        opening_tag_node = nodes.raw('', opening_tag, format='html')

        text = '\n'.join(self.content)
        content_node = nodes.container(rawsource=text)
        self.state.nested_parse(self.content, self.content_offset, content_node)

        closing_tag_node = nodes.raw('', "</details>", format='html')

        result_node = nodes.container()
        result_node += [opening_tag_node, content_node, closing_tag_node]
        return [result_node]
