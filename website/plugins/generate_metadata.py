import typing
from blinker import signal

from nikola.plugin_categories import SignalHandler
from nikola.utils import get_logger, STDERR_HANDLER
from nikola.nikola import Nikola

from plugins.metadata import SiteMetadata, PageMetadata

class MetadataGenerator(SignalHandler):
    """
    Generate site structure object and add it to the site object

    The primary goal of this plugin is to prepare metadata that
    can be used by other plugins, eg to generate breadcrumbs or
    links to next/prev pages.
    """

    name = 'generate_metadata'

    def add_metadata(self, event) -> None:
        self.site.metadata = SiteMetadata(self.site)

        for page in self.site.pages:
            page.metadata = PageMetadata(page, self.site.metadata)


    def set_site(self, site: Nikola) -> None:
        self.site = site
        self.logger = get_logger(self.name, STDERR_HANDLER)

        self.ready = signal('scanned')
        self.ready.connect(self.add_metadata)
