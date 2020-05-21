# https://stackoverflow.com/questions/33533148
from __future__ import annotations
from typing import List, Tuple

from nikola.plugin_categories import ShortcodePlugin
from nikola.nikola import Nikola
from nikola.post import Post
from nikola.utils import get_logger

from plugins.metadata import PageDir, split_path

class IndexGenerationShortcode(ShortcodePlugin):
    """Generates website structure. Requires SiteMetadata attribute in site."""

    def __init__(self):
        self.name = "generate_index"
        self.logger = get_logger(self.name)


    def set_site(self, site: Nikola) -> None:
        site.register_shortcode(self.name, self.generate_index)


    def generate_index(
        self,
        site: Nikola,
        post: Post,
        data: str = None,
        lang: str = None
    ) -> Tuple[str, List[str]]:
        """
        Generate a hierarchical list of all pages on the website.

        Ouput: a HTML string (nested <ul> elements containing <a> elements)
        and a list of file dependencies.
        """
        if not post.metadata.is_index_page:
            raise RuntimeError(f'Attempt to generate index on "{post.permalink()}" which is not an index page!')

        # index pages can list contents of arbitrary directory
        # find first which directory the page refers to
        index_root: PageDir = site.GLOBAL_CONTEXT["metadata"].structure()
        index_path: str = post.meta[post.default_lang]["index_path"]
        if index_path == ".":
            for directory_name in split_path(post.permalink()):
                index_root = index_root.enter(directory_name)
        elif index_path != "/":
            for directory_name in split_path(index_path):
                index_root = index_root.enter(directory_name)

        self.logger.info(f"generating index structure for {post.permalink()} that starts in {index_path}")
        html_result: str = generate_hierarchical_html(index_root)

        # We need to regenerate indexes every time a page is added or removed.
        # We can not return wildcard paths or generally - paths which do not exist
        # but there is a hidden (undocumented) feature that does exactly this.
        # https://github.com/getnikola/nikola/issues/3293#issuecomment-523210046
        file_dependencies = ["####MAGIC####TIMELINE"]

        return html_result, file_dependencies


def generate_hierarchical_html(root_dir: PageDir) -> str:
    """Generate HTML code representing hierarchical list of links"""

    # There is no efficient way of appending to a string in Python.
    # Pass a list as an output parameter, append to it and then join elements.
    html_parts: List[str] = []
    generate_hierarchical_html_impl(root_dir, html_parts)
    return "".join(html_parts)


def generate_hierarchical_html_impl(root_dir: PageDir, html_parts: List[str]) -> None:
    html_parts.append("<ul>")

    for page in root_dir.pages():
        html_parts.append(f'<li><a href="{page.permalink()}">{page.title()}</a></li>')

    for subdir in root_dir.subdirs():
        html_parts.append(f'<li><a href="{subdir.index_page().permalink()}">{subdir.index_page().title()}</a>')
        generate_hierarchical_html_impl(subdir, html_parts)
        html_parts.append("</li>")

    html_parts.append("</ul>")
