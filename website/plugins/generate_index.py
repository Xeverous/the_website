# https://stackoverflow.com/questions/33533148
from __future__ import annotations
from typing import List, Tuple

from nikola.plugin_categories import ShortcodePlugin
from nikola.nikola import Nikola
from nikola.post import Post


class IndexGenerationShortcode(ShortcodePlugin):
    name = "generate_index"

    def set_site(self, site: Nikola) -> None:
        """Set the site."""
        # WARNING: weird workaround for warning/error of registering callback
        # if case something breaks or it is repaired in the future refer to this issue
        # https://github.com/getnikola/nikola/issues/3286
        # super(IndexGenerationShortcode, self).set_site(site)
        site.register_shortcode("generate_index", self.handler)

    def handler(
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
        # site.pages: List[Post]
        root_dir: PageDir = make_tree(site.pages)
        html_result = generate_hierarchical_html(root_dir)

        return html_result, list()


class PageDir:
    def __init__(self, directory: str, pages: List[Post] = None, subdirs: List[PageDir] = None):
        self.directory = directory
        self.pages = pages or []
        self.subdirs = subdirs or []

    def traverse(self, directory: str) -> PageDir:
        """Return a nested directory object. If it does not exist, create one and then return it."""
        for subdir in self.subdirs:
            if subdir.directory == directory:
                return subdir

        self.subdirs.append(PageDir(directory))
        return self.subdirs[-1]


def directories_from_path(path: str) -> List[str]:
    """
    Strip slashes from the path and split the resulting directories into a list

    Example: "/foo/bar/baz/quux/" => ["foo", "bar", "baz", "quux"]
    """
    return path.strip("/").split("/")


def make_tree(pages: List[Post]) -> PageDir:
    root_dir = PageDir("/")
    for page in pages:
        current = root_dir
        for directory in directories_from_path(page.permalink()):
            current = current.traverse(directory)
        current.pages.append(page)

    return root_dir


def make_li_element(page: Post) -> str:
    """Make a HTML element: <li><a href="path">text</a></li>"""
    return '<li><a href="{0}">{1}</a></li>'.format(page.permalink(), page.title())


def generate_hierarchical_html(root_dir: PageDir) -> str:
    """Generate HTML code representing hierarchical list of links"""

    html_parts: List[str] = []
    generate_hierarchical_html_impl(root_dir, html_parts)
    return "".join(html_parts)


def generate_hierarchical_html_impl(root_dir: PageDir, html_parts: List[str]) -> None:
    if not root_dir.pages and not root_dir.subdirs:
        return

    html_parts.append("<ul>")
    html_parts.append(root_dir.directory)

    for page in root_dir.pages:
        html_parts.append(make_li_element(page))

    for subdir in root_dir.subdirs:
        generate_hierarchical_html_impl(subdir, html_parts)

    html_parts.append("</ul>")
