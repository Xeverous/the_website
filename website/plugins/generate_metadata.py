from blinker import signal

from nikola.plugin_categories import SignalHandler
from nikola.utils import get_logger
from nikola.nikola import Nikola

from plugins.metadata import SiteMetadata, PageMetadata

class MetadataGenerator(SignalHandler):
    """
    Generate site structure object and add it to the site object

    The primary goal of this plugin is to prepare metadata that
    can be used by other plugins, eg to generate breadcrumbs or
    links to next/prev pages.

    Every Post object (which represents a post or a page) gets a new
    "metadata" subobject. Do not confuse it with page.meta[page.default_lang]
    which is Nikola-provided subobject that holds information specified at
    the top of the file.
    """

    name = 'generate_metadata'

    def add_metadata(self, event) -> None:
        self.logger.info("generating metadata for the site")
        metadata = SiteMetadata(self.site)
        self.site.GLOBAL_CONTEXT["metadata"] = metadata

        for page in self.site.pages:
            self.logger.info(f"generating metadata for page {page.permalink()}")
            page.metadata = PageMetadata(page, metadata)


    def set_site(self, site: Nikola) -> None:
        self.site = site
        self.logger = get_logger(self.name)

        # Since the primary goal of this plugin is to prepare data for other plugins,
        # it should be run as early as possible and when necessary information is available.
        # Thus, the plugin registers itself to be run when Nikola has finished scanning files.
        self.ready = signal('scanned')
        self.ready.connect(self.add_metadata)
