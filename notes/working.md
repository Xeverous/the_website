# working with the code

## build system

There are at least few hundreds of static site generators. While the story in choosing [Nikola](https://getnikola.com) is pretty long, below is a short list of rationale:

- Majority of static site generators are only for documentation or blogs. This project requires support of arbitrary directory trees and can not have inherent limitations how pages are laid out.
- No fixed or artificially limited CSS/JS implementation or HTML templates.
- Support for custom input data formats. Support for rich input format extensions.
- Support for plugins and custom build hooks/steps.
- Nikola uses already well-established projects (Docutils, Jinja2) which means good support and no risk of committing to something badly designed. This also allows easy transfer to potentially completely custom build implementation if such thing is needed in the future - right now Nikola is more or less code that only ties everything together.
- Nikola is in Python which is a pretty common "scripting language choice" for C++ programmers.

Still, if you think you can do better (with other framework or a completely custom build) - certainly open an issue and write your rationale. The core goal of the build process is to be able to write semi-rich pages in human-readable format.

The current recommended input format for pages is [reStructuredText](https://docutils.sourceforge.io/rst.html) with this rationale:

- Unlike Markdown, it has an actual specification. No problems with ever-diverging implementations.
- Supports nesting block elements and custom block elements.

## general notes

Note that this site completely replaces Nikola's default templates by using its own, parent-less theme so a lot of things that are mentioned in Nikola's documentation do not apply to this site or apply but have different effect. Multiple built-in features such as charts, galleries, timeline, anything blog-related, listings etc are not being used and had their respective files removed. This includes HTML templates, CSS and JS. Everything generation-related (HTML templates, CSS, JS) should be put into this site custom theme directory. Watch out when reading anything from https://getnikola.com/handbook.html as it implicitly assumes a blog with base theme. Better read https://getnikola.com/theming.html because that is the place where most functionality of this site comes from. Again, remember that this site theme has no base and absolutely all HTML templates are custom-made.

`PAGES` and `POSTS` in `conf.py` have been modified. File extension has been changed from `tmpl` to `html` because while the `tmpl` is more clear about the source being a template, multiple editing tools work better with `html` extension by default and they already are smart enough to detect and highlight template code in HTML files.

List of built-in plugins: https://github.com/getnikola/nikola/issues/3281#issuecomment-518035610

Nikola internals description: https://getnikola.com/internals.html

Since this site uses custom plugins and hooks custom build steps, any errors should be taken seriously. Throw exceptions on any significant problem. Use the logger to warn if anything looks suspicious but the build can proceed.

## building

- `export NIKOLA_SHOW_TRACEBACKS=1` when debugging. `unset NIKOLA_SHOW_TRACEBACKS` to clear it. Note that opening new shell clears environmental variables.
- Error that address already in use when launching Nikola server: previous Nikola execution was not stopped gracefully. `sudo killall nikola` should fix it.
- If you spot multiple errors in the website build log, focus on the first ones first. A lot of further errors can be caused by previous ones.

## writing pages

Check test pages to see how each Markdown and reST element is written and rendered.

Any file intended to be compiled must have metadata specified (https://getnikola.com/handbook.html#metadata-fields). Note that any page can have custom metadata fields.

Mandatory metadata fields:

- `title` - will be used in `<title>` in generated HTML.
- `slug` - used as the component of the page URL, should be short and consist only of `a-z0-9-_`. Usually based on the title.
- `description` - will be used used in `<meta>` in generated HTML for SEO.
- `author` - author name (string), will be used in generated HTML. Not required for *index pages*.

Extra metadata fields (generally not needed):

- `date` - creation time (ISO 8601).
- `updated` - last modification time (ISO 8601).
- `template` - override default HTML template used to render the page.
- `pretty_url` - this site has globally enabled generation of pretty urls (`foo/index.html` instead of `foo.html`). This metadata tag overrides the setting for the given page. Note that pages with slug `index` will implicitly have pretty URL disabled. Setting this field to `False` should only be needed for special pages (e.g. 404 page).
- `breadcrumb` (custom) - set to `False` if for some reason the page should not get a breadcrumb (e.g. 404 page).
- `index_path` - makes the page an **index page** and allows to use `generate_index` *shortcode*.

Unused metadata fields:

- `tags` - comma-separated lists of tags (no uses found yet, might be used in the future).
- `category` - like tags, but a page/post can have only one (no uses found yet, might be used in the future).
- `status` - one of: `published` (default) / `featured` / `draft` / `private`; can be used to disable page generation.
- `has_math` - enables Nikola's built-in support of MathJax and KaTeX. Currently not used.
- `guid` - for RSS and Atom feeds.
- `link` - link to original source content - not used because:
  - This allows only 1 external source link per page/post.
  - reST offers better mechanism for referencing external sources.
- `type` - type of the post, affects Nikola's generation but note that this site completely replaces Nikola's default templates, therefore it would not work.
- `data` - path to a JSON/YAML/TOML file that will be mapped to Python for the given `nikola.post.Post` instance; accessible by `.data('key')`, no use found so far. I prefer to write reST plugins which take input from directive calls within the text than to rely on Nikola-specific mechanisms.
- `filters` - optional post-processing stuff built-in into Nikola.
- `hidetitle` - no use since this site has own templates.
- `nocomments` - this site currently does not use any comment system.

**Index pages** are special pages intended to act as the equivalent of directories. They exist so that users can "move up" (by clicking links in the breadcrumb or trimming URL) to get a list of pages with the same prefix instead of a 404 error. A typical index page should be named `index.rst` and look as follows:

```
.. title: <TITLE BASED ON PARENT DIRECTORY NAME>
.. slug: index
.. description: <DESC>
.. index_path: .

:sc:`{{% generate_index %}}`
```

A typical normal page (no requirements on the file name - the slug will be used to generate URL):

```
.. title: <TITLE>
.. slug: <SLUG>
.. description: <DESC>
.. author: <NAME>
```

The slug should be `index` if the page lies in its own directory (not sharing this directory with any other page). This is so for pages that contain calls to `cch` and `ansi` plugins. The directory name already specifies the title so the `index` will enable pretty URL.

### writing pages - code snippets

Support enabled through `rest_highlighter` plugin.

Specified paths are mandatory. If the path begins with `/`, it is relative to the `conf.py` file, otherwise it is relative to the file containing the directive.

#### custom code highlight

TODO describe `cch` (inline role and directive).

#### ANSI highlight

How to embed:

```
.. ansi::
    :ansi_path: path/to/file.txt
```

How to generate rich text with ANSI escapes:

```
# run the command in a separate typescript shell
script -q -c "command that prints colored text" output.txt
# remove script opening and closing logs
gawk -i inplace 'NR>2 {print last} {last=$0}' output.txt
# trim trailing lines (https://stackoverflow.com/a/44850844/4818802)
sed -n '/^$/ !{x;/\n/{s/^\n//;p;s/.*//;};x;p;}; /^$/H' -i output.txt
# remove ^M (CR, \r) from the file
sed 's/\r//g' -i output.txt
```

This requires gawk (GNU awk) 4.1.0+ and GNU sed.

### other notes

I have noticed several typos, below is a list of correct expressions:

- e.g.
- i.e.
- etc.
- Cel**s**ius
- it's (short for it is) vs its (describes ownership)
- advised (verb) vs adviced (noun) (common phrase: it's advi**s**ed)
- reminder (to not forget) vs remainder (result of modulo)
- `admonition:: info` should be `admonition:: note`
- *compile-time* should be *compile time* (and analogically *link time*)

## working with CSS

Use root-relative paths when linking global stylesheets to avoid problems in nested pages. For example, `foo/bar/page.html` would need to use `../../styles.css` to reference `styles.css` file, and the path to CSS could break every time the page is moved. `/assets/css/styles.css` will always work as long as assets themselves are not moved.

Xeverous: I'm not a web developer. I learned CSS from https://www.internetingishard.com. Many things follow examples from this tutorial as I do not have any other experience.

## working with Jinja2 templates

- Documentation and tutorial: https://jinja.palletsprojects.com/en/2.11.x/templates/
- Use `extends` or `import`. Nikola does not support `include` (note that `import` has a superset of `include` features).
- Do not use `with context` to be able to access variables supplied by Nikola in templates, this inhibits caching (https://jinja.palletsprojects.com/en/2.11.x/templates/#import-visibility) pass any necessary data through macro parameters instead.
- List of stuff predefined in templates: https://getnikola.com/template-variables.html
- When writing Python code for templates, always write it so that templates use functions:
  - If `obj.name` does not exist it will silently evaluate to an empty string.
  - If `obj.name()` does not exist it will loudly fail with an exception.
- You should not check breadcrumbs like `if page.metadata.breadcrumb()` because a page with an empty list may still want to have a breadcrumb. Use `page.metadata.has_breadcrumb()` instead which differentiates between an empty list and `None`.

## working with Python code

- `conf.py` is provided by Nikola. Nikola does all core logic. All of website custom code are Nikola Python plugins.
- Plugins have their respective `.py` and `.plugin` files.
  - `.plugin` file tells Nikola where to hook the code that is placed there and provides some meta information about it.
  - `.py` file is obviously plugin implementation. There is no problem is sharing code between plugins - just make it a separate file and import common code in plugin implementation files.
  - 2 things are common for every plugin
    - there is some specific interface to implement (which depends on the plugin category)
	- there is an interface to report file dependencies (if the plugin uses extra files, this allows to tell Nikola necesssary information to support incremental builds)
- For historical reasons, Nikola uses `Post` class for both posts and pages even though posts are pages with specific properties. Thus, a lot of Python code has `Post` instances named `page`.
- Site plugins should raise exceptions on problems that may cause bigger problems later. Otherwise, issue warnings to the log.
- Do not `import logging`, `from nikola.utils import get_logger` instead and use `get_logger(__name__)`.

Plugins description

- **rest_highlighter** - adds custom *directive* and *role* (reST terms) that generate highlighted code blocks using ACH.
- **generate_metadata** - generates metadata objects (1 global and 1 for each page) that are used by other plugins.
- **generete_index** - generates index of specific directory tree when `generete_index` shortcode is invoked.
