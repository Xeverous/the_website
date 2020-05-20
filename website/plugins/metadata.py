# https://stackoverflow.com/questions/33533148
from __future__ import annotations
from typing import List, Tuple

from nikola.post import Post
from nikola.nikola import Nikola
from nikola.utils import get_logger

class SiteMetadata:
    def __init__(self, site: Nikola):
        self.structure = parse_site_structure(site.pages)
        self.log_correctness(self.structure)

    def __repr__(self) -> str:
        lines: List[str] = []
        build_structure_repr(self.structure, lines, 0)
        return "\n".join(lines)

    def log_correctness(self, root_dir: PageDir) -> None:
        """
        Check and log any suspicions in the structure

        index   child dirs   child pages
          +        -             -       WARN: useless index
          +                              OK
          -        -             -       WARN: empty directory
          -                              ERROR: missing index
        """
        logger = get_logger(__name__)
        if root_dir.index_page:
            if not root_dir.subdirs and not root_dir.pages:
                logger.warn(f'Directory "{root_dir.directory_name}" contains an index page but no child pages or directories')
        else:
            if not root_dir.subdirs and not root_dir.pages:
                logger.warn(f'Directory "{root_dir.directory_name}" is empty')
            else:
                logger.error(f'Directory "{root_dir.directory_name}" has child pages or directories but does not contain an index!')

        for subdir in root_dir.subdirs:
            self.log_correctness(subdir)

# for debugging only
def build_structure_repr(page_dir: PageDir, lines: List[str], recursion_depth: int) -> None:
    indent = "    " * recursion_depth

    lines.append(f"{indent}INDEX: {page_dir.index_page is not None}")

    for page in page_dir.pages:
        lines.append(f'{indent}"{page.title()}"')

    for subdir in page_dir.subdirs:
        lines.append(f"{indent}{subdir.directory_name}")
        build_structure_repr(subdir, lines, recursion_depth + 1)


class PageDir:
    """Represents a directory which may contain pages and subdirectories"""

    def __init__(self, directory_name: str, index_page: Post = None):
        self.directory_name = directory_name
        self.index_page = index_page
        self.pages: List[Post] = []
        self.subdirs: List[PageDir] = []

    def enter_or_create(self, directory_name: str) -> PageDir:
        """Return a nested directory object. If it does not exist, create one and then return it."""
        for subdir in self.subdirs:
            if subdir.directory_name == directory_name:
                return subdir

        self.subdirs.append(PageDir(directory_name))
        return self.subdirs[-1]

    def enter(self, directory_name: str) -> PageDir:
        """Return a nested directory object. If it does not exist, raise an exception"""
        for subdir in self.subdirs:
            if subdir.directory_name == directory_name:
                return subdir

        raise RuntimeError(f'Directory "{self.directory_name}" has no child directory "{directory_name}"!')



def split_path(path: str) -> List[str]:
    """
    Strip slashes from the path and split the resulting directories into a list

    Example: "/foo/bar/baz/quux/" => ["foo", "bar", "baz", "quux"]
    """
    return path.strip("/").split("/")


def parse_site_structure(pages: List[Post]) -> PageDir:
    root_dir = PageDir("")

    for page in pages:
        current_dir = root_dir
        index_path = page.meta[page.default_lang].get("index_path")
        if index_path:
            if index_path == ".":
                for directory_name in split_path(page.permalink()):
                    current_dir = current_dir.enter_or_create(directory_name)
            elif index_path != "/":
                for directory_name in split_path(index_path):
                    current_dir = current_dir.enter_or_create(directory_name)
            current_dir.index_page = page
        else:
            # skip last element because we are using PRETTY_URLS - every non-index page
            # becomes an index.html file in an extra directory named as its slug
            for directory_name in split_path(page.permalink())[:-1]:
                current_dir = current_dir.enter_or_create(directory_name)
            current_dir.pages.append(page)

    return root_dir

# note: Nikola uses Post class for both blog posts and standalone pages
class PageMetadata:
    def __init__(self, page: Post, site_metadata: SiteMetadata):
        self.is_index_page = "index_path" in page.meta[page.default_lang]
        self._breadcrumb = make_page_breadcrumb(page, site_metadata.structure)
        check_page_slug(page)

    def has_breadcrumb(self) -> bool:
        return self._breadcrumb is not None

    def breadcrumb(self):
        return self._breadcrumb

def make_page_breadcrumb(page: Post, site_structure: PageDir):
    breadcrumb = page.meta[page.default_lang].get("breadcrumb")
    # TODO should this compare to "False"? (a string?)
    if breadcrumb is None or breadcrumb != "False":
        return generate_breadcrumb(page.permalink(), site_structure)
    else:
        return None

def check_page_slug(page: Post) -> None:
    # for consistency, page slug should be the same as the filename
    file_name = page.translated_source_path(page.default_lang).split("/")[-1]
    file_ext = page.source_ext()
    page_slug = page.meta[page.default_lang].get("slug")
    if page_slug != "index" and page_slug + file_ext != file_name:
        logger = get_logger(__name__)
        logger.warn(f'page {page.permalink()} uses slug "{page_slug}" which is different from source file name "{file_name}"')

class BreadcrumbEntry:
    def __init__(self, link: str, name: str):
        self._link = link
        self._name = name

    def name(self) -> str:
        return self._name

    def link(self) -> str:
        return self._link

def generate_breadcrumb(page_path: str, structure: PageDir) -> List[BreadcrumbEntry]:
    """
    Generate a list of breadcrumb entries consisting of parent directory index pages

    Note that for first-depth pages the result of this function will be an empty list.
    This is intentional: HTML templates already add extra elements around: they prepend
    root index page and append the current page title. The HTML template is effectively:
    root_index_page / this_function_result / page.title().

    This also means that you should not check it like "if page.metadata._breadcrumb"
    in HTML templates because an empty list still means the desire to generate a
    breadcrumb. Use "page.metadata.has_breadcrumb()" instead which differentiates
    between an empty list and None.
    """
    directory_names = split_path(page_path)
    if len(directory_names) == 0:
        raise RuntimeError(f"""Failed generation of a breadcrumb for "{page_path}"!
        Root directory pages should not have breadcrumbs.
        Add missing "breadcrumb: False" to page's metadata if this is the case.""")

    result: List[BreadcrumbEntry] = []
    current_dir = structure
    # skip last element (for any path) because:
    # - we are using PRETTY_URLS - every non-index page becomes
    #   an index.html file in an extra directory named as its slug
    # - every index page lists itself as its parent directory index page
    #   we skip last element to avoid mentioning the same page twice
    for d in directory_names[:-1]:
        current_dir = current_dir.enter(d)
        result.append(BreadcrumbEntry(current_dir.index_page.permalink(), current_dir.index_page.title()))

    return result
