# https://stackoverflow.com/questions/33533148
from __future__ import annotations
from typing import List, Optional

from nikola.post import Post
from nikola.nikola import Nikola
from nikola.utils import get_logger

class SiteMetadata:
    def __init__(self, site: Nikola):
        self._structure = parse_site_structure(site.pages)
        self._structure.sort()
        log_correctness(self.structure())
        self._sidebar = make_sidebar()
        verify_sidebar(self.sidebar(), site.pages)

    def __repr__(self) -> str:
        lines: List[str] = []
        build_structure_repr(self.structure(), lines, 0)
        return "\n".join(lines)

    def structure(self) -> PageDir:
        return self._structure

    def sidebar(self) -> Sidebar:
        return self._sidebar

def log_correctness(root_dir: PageDir) -> None:
    """
    Check and log any suspicions in the structure

    index   child dirs or pages
      +             -              WARN: useless index
      +             +              OK
      -             -              WARN: empty directory
      -             +              ERROR: missing index
    """
    logger = get_logger(__name__)
    if root_dir.index_page():
        if not root_dir.subdirs() and not root_dir.pages():
            logger.warning(f'Directory "{root_dir.directory_name()}" contains an index page but no child pages or directories')
    else:
        if not root_dir.subdirs() and not root_dir.pages():
            logger.warning(f'Directory "{root_dir.directory_name()}" is empty')
        else:
            logger.error(f'Directory "{root_dir.directory_name()}" has child pages or directories but does not contain an index!')

    for subdir in root_dir.subdirs():
        log_correctness(subdir)

# for debugging only
def build_structure_repr(page_dir: PageDir, lines: List[str], recursion_depth: int) -> None:
    indent = "    " * recursion_depth

    lines.append(f"{indent}INDEX: {page_dir.index_page() is not None}")

    for page in page_dir.pages():
        lines.append(f'{indent}"{page.title()}"')

    for subdir in page_dir.subdirs():
        lines.append(f"{indent}{subdir.directory_name()}")
        build_structure_repr(subdir, lines, recursion_depth + 1)


class PageDir:
    """Represents a directory which may contain pages and subdirectories"""

    def __init__(self, directory_name: str, index_page: Post = None):
        self._directory_name = directory_name
        self._index_page = index_page
        self._pages: List[Post] = []
        self._subdirs: List[PageDir] = []

    def directory_name(self) -> str:
        return self._directory_name

    def set_index_page(self, page: Post) -> None:
        self._index_page = page

    def index_page(self) -> Optional[Post]:
        return self._index_page

    # does not include index page
    def pages(self) -> List[Post]:
        return self._pages

    def subdirs(self) -> List[PageDir]:
        return self._subdirs

    def sort(self) -> None:
        self._pages.sort(key=lambda page: page.permalink())
        self._subdirs.sort(key=lambda subdir: subdir.directory_name())
        for subdir in self.subdirs():
            subdir.sort()

    def enter_or_create(self, directory_name: str) -> PageDir:
        """Return a nested directory object. If it does not exist, create one and then return it."""
        for subdir in self.subdirs():
            if subdir.directory_name() == directory_name:
                return subdir

        self.subdirs().append(PageDir(directory_name))
        return self.subdirs()[-1]

    def enter(self, directory_name: str) -> PageDir:
        """Return a nested directory object. If it does not exist, raise an exception"""
        for subdir in self.subdirs():
            if subdir.directory_name() == directory_name:
                return subdir

        raise RuntimeError(f'Directory "{self.directory_name()}" has no child directory "{directory_name}"!')


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
            # This is not done at the point of PageDir construction because
            # the information which subpage is an index page is only available
            # after all subpages have been processed.
            current_dir.set_index_page(page)
        else:
            # skip last element because we are using PRETTY_URLS - every non-index page
            # becomes an index.html file in an extra directory named as its slug
            for directory_name in split_path(page.permalink())[:-1]:
                current_dir = current_dir.enter_or_create(directory_name)
            current_dir.pages().append(page)

    return root_dir

# note: Nikola uses Post class for both blog posts and standalone pages
class PageMetadata:
    def __init__(self, page: Post, site_metadata: SiteMetadata):
        self.is_index_page = "index_path" in page.meta[page.default_lang]
        self._breadcrumb = make_page_breadcrumb(page, site_metadata.structure())
        check_page_slug(page, self.is_index_page)
        check_required_metadata(page)

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

def check_page_slug(page: Post, is_index_page: bool) -> None:
    logger = get_logger(__name__)
    index_page_slug = "index"
    # for consistency, page slug should be the same as the filename
    file_name = page.translated_source_path(page.default_lang).split("/")[-1]
    file_ext = page.source_ext()
    page_slug = page.meta[page.default_lang].get("slug")
    if page_slug != index_page_slug and page_slug + file_ext != file_name:
        logger.warning(f'page {page.permalink()} uses slug "{page_slug}" which is different from source file name "{file_name}"')
    # for consistency, index pages (that is, pages with "index_path" specified) should have slug "index"
    if is_index_page and page_slug != index_page_slug:
        logger.warning(f'page {page.permalink()} is an index page but has slug "{page_slug}" which is different from expected "{index_page_slug}"')

def check_required_metadata(page: Post) -> None:
    check_required_metadata_field(page, "title")
    check_required_metadata_field(page, "slug")
    check_required_metadata_field(page, "description")
    check_required_metadata_field(page, "author")

def check_required_metadata_field(page: Post, field_name: str) -> None:
    logger = get_logger(__name__)
    field = page.meta[page.default_lang].get(field_name)
    if not field:
        logger.warning(f'page {page.permalink()} has missing "{field_name}" metadata field')

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

    This also means that you should not check it like "if page.metadata.breadcrumb()"
    in HTML templates because an empty list still means the desire to generate a
    breadcrumb. Use "page.metadata.has_breadcrumb()" instead which differentiates
    between an empty list and None.
    """
    directory_names = split_path(page_path)
    if len(directory_names) == 0:
        raise RuntimeError(f"""Failed to generate breadcrumb for "{page_path}"!
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
        if current_dir.index_page() is None:
            get_logger(__name__).error(f'Failed to generate breadcrumb for "{page_path}", missing index page(s)')
            return []
        result.append(BreadcrumbEntry(current_dir.index_page().permalink(), current_dir.index_page().title()))

    return result

class Sidebar:
    """
    Represents sidebar on the page.

    Do not add any links directly to HTML templates - add them here instead.
    Instance of this class is passed then to templates which:
    - avoids copy-paste errors
    - lets Python code verify that all the data here is actually correct
    """
    def __init__(self, sections: List[SidebarSection]):
        self._sections = sections

    def sections(self) -> List[SidebarSection]:
        return self._sections

class SidebarSection:
    def __init__(self, title: str, description: str, pages: List[SidebarPage]):
        self._title = title
        self._description = description
        self._pages = pages

    def title(self) -> str:
        return self._title

    def description(self) -> str:
        return self._description

    def pages(self) -> List[SidebarPage]:
        return self._pages

class SidebarPage:
    def __init__(self, title: str, link: str):
        self._title = title
        self._link = link

    def title(self) -> str:
        return self._title

    def link(self) -> str:
        return self._link

def verify_sidebar(sidebar: Sidebar, all_pages: List[Post]):
    logger = get_logger(__name__)

    for section in sidebar.sections():
        if section.title() == "":
            logger.warning(f'sidebar section with empty title, it has description: "{section.description()}"')
        if len(section.pages()) == 0:
            logger.warning(f'sidebar section "{section.title()}" has no pages')

        for page in section.pages():
            if page.title() == "":
                logger.warning(f'untitled page in sidebar section "{section.title()}"')
            if page.link() == "":
                logger.warning(f'page "{page.title()}" in sidebar section "{section.title()}" has empty link')

            page_found = False
            for p in all_pages:
                # for unknown reason, permalinks end with "/"
                if page.link() == p.permalink():
                    page_found = True
                    break

            if not page_found:
                logger.warning(f'sidebar page "{page.title()}" link "{page.link()}" is invalid')

def make_sidebar() -> Sidebar:
    return Sidebar([
        SidebarSection("C++ tutorials", "Learn C++ from begin() to the end() (and beyond) or use knowledge and experience gained in other languages in the accelerated tutorial.", [
            SidebarPage("beginner", "/cpp/tutorials/beginner/"),
            SidebarPage("accelerated", "/cpp/tutorials/accelerated/"),
            SidebarPage("templates", "/cpp/tutorials/templates/")
        ]),
        SidebarSection("C++ how-to", "Common and specific tasks explained.", [
            SidebarPage("standard library components", "/cpp/how_to/std_lib/"),
            SidebarPage("language features", "/cpp/how_to/language/")
        ]),
        SidebarSection("C++ utilities", "Various metarials with concentrated information.", [
            SidebarPage("C++ cheatsheets", "/cpp/utility/cheatsheets/"),
            SidebarPage("C++ FAQ", "/cpp/utility/cpp_faq/"),
            SidebarPage("C++ myths", "/cpp/utility/cpp_myths/"),
            SidebarPage("glossary", "/cpp/utility/glossary/"),
            SidebarPage("(all articles)", "/cpp/utility/")
        ]),
        SidebarSection("misc / meta", "About this website and its authors.", [
            SidebarPage("about", "/about/"),
            SidebarPage("website FAQ", "/meta/site_faq/"),
            SidebarPage("Markdown test page", "/meta/markdown_test/"),
            SidebarPage("reStructuredText test page", "/meta/rest_test/")
        ])
    ])
