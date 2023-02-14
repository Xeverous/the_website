from nikola.plugin_categories import RestExtension
from docutils import nodes

from docutils.parsers.rst import roles

class RestHighlighter(RestExtension):
    """Plugin for custom "s" reST role."""

    name = "strikethrough"

    def set_site(self, site):
        self.site = site
        roles.register_local_role('s', strikethrough)
        return super().set_site(site)

# https://stackoverflow.com/a/62493316/4818802
def strikethrough(name, rawtext, text, lineno, inliner, options={}, content=[]):
    roles.set_classes(options)
    # adding a class is better than producing raw HTML because it supports any output format
    options.setdefault('classes', []).append("strikethrough")
    return [nodes.inline(rawtext, text, **options)], []
