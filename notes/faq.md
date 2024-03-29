# FAQ

## Can I add a certain binary file (e.g. image) as-is to the website and use it on some pages?

Yes, just put it in the `files` directory - everything there is copied as-is to the output.

## What's the deal with index pages?

The website is designed around the concept of a directory/file tree. To avoid 404 errors, index pages are pages to display when a link to directory is entered. They are named "index" because of how browsers default to showing `index.html` file when given a directory path. Index pages can contain content just like any other page, but most of them will only list subpages from their directory (listings are autogenerated).

## What's wrong with Markdown?

While the format has great simplicity, it has failed to accomplish 1 fundamental thing: DOCUMENTATION. The original Markdown implementation did not have any, the specification was therefore implied by the implementation. As with many things, it had bugs. But because there was no specification, there was no source to refer to when something was (subjectively) wrong. Soon new implementations arrived with different "bugs". Currently, apart from fundamental things such as bold and italic text, any rendered Markdown on places like StackOverflow, GitHub, GitLab, Visual Studio Code Markdown preview, Python docutils, Reddit, etc. has different behavior. I'm not going to support this kind of mess, especially when many renderers vary significantly on whitespace behavior and support for extensions like inline HTML or ```-style code blocks, which work on new reddit but don't work on old reddit, even with RES.

Very simple files (like this one) can use Markdown as they are indended to be read online directly from repository, without going through website build process. But I will not care to support complex webpages written in Markdown - use a different format instead.

There are 2 documented forks of Markdown - Kramdown and CommonMark but at this point it's just better to use reStructuredText.

## Is it possible to nest shortcodes (Nikola feature, e.g. `{{% name %}}`)?

Nikola does not support it explicitly, but it is possible to implement such thing by adding opening and closing blocks as 2 separate shortcode plugins + some code which verifies all nested shortcodes are properly closed and in order. IMO not worth the effort given that reStructuredText offers nestable directives, which can be custom.

## Can you describe the order of all build steps (e.g. scanning files, invoking plugins, generating HTML, copying files)?

There is no fixed order. Nikola uses doit, which is an incremental build build system that can run tasks in parallel. If there are any dependencies between certain tasks (as it is the case with many plugins) they need to be stated explicitly by the plugin itself. Plugins have an interface to express which files they depend on.

Of couse there is some pattern within file dependencies so here is a simplified list of steps of the build process:

- Nikola loads `conf.py` and plugins.
- If it's an incremental build, files are scanned for date.
- Source files (e.g. Markdown, reStructuredText) are being passed through respective compilers. This site compiles them to HTML. Compilers may invoke their plugins (as it is the case for ACH).
- Compiled HTML portions are not fully functional HTML (they do not contain `<head>` etc), these are passed through HTML templates engine - this site uses Jinja2. Check existing templates to see which data and how is output. Majority of pages go through the same HTML template, intended for lessons and side articles.
- Files in `files` directory are copied 1:1 to the output directory `output`.

## Why Nikola?

The answer to this question is so long that I plan to make a separate article on the website about it. The tl;dr is that while there are few hundred available static site generators, ~99% of them are only suited for blogs or documentation, neither of which this site is. Turns out that there weren't many real candidates to choose from so the final decision wasn't that hard. Nikola has great inner architecture and basically everything can be replaced. Even the built-in Markdown and reST compilers are written as plugins, so one can define another compiler that is equally powerful as the built-in ones. To me this sounds familiar to C++ design, where user-defined types are as powerful with operator overloading as the built-in types.

Nikola is a relatively small project and the only thing it does is tying together text compilers (e.g. Markdown, reST), output generators (e.g. Jinja2, Mako) and a build system (doit). If at any point in future I need even more customization or Nikola gets abandoned, I can easily reconnect the pieces which themselves are pretty mature projects.

For questions why not Hugo - Go isn't as popular as Python and Python plays very well with C and C++. Python is commonly the second best-known language for C++ programmers.

## Can I help with the site by means other than writing/editing articles?

Yes, in fact a lot of help is needed for CSS, JS and Python code. There is a lot of website-tech topics that are still unresolved. Just open an issue and specify what you are skilled with.

## Do you really like writing such questions?

Yes, as much as this (and many other questions in this FAQ) are fake. They are "fake" as they have never actually been asked but I predicted some would like to read answers to them. Plus there are some important aspects that I would like to share in FAQ-style form.

## If I contribute something to the site, can my work have a different license?

Depends what the work is.

- Editing someone else's articles - no, the license is the will of the author.
- Your own articles - yes as you are the author.
- Website internal code that builds everything:
    - editing code: same license
    - new code: must be compatible with GPL 3.0.

Note that the project uses separate licenses for internal code and article text - the first is GPL 3.0, the latter depends on the author, which in my case will usually be CC-BY-SA 4.0.
