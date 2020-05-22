.. title: reStructuredText test
.. slug: rest_test
.. date: 2020-05-20 13:08:52 UTC+02:00
.. tags:
.. category:
.. description: reStructuredText test page
.. type: text
.. author: Xeverous

The following page presents reStructuredText examples and how they look on the site. Compare the source of this page with how it looks on the site (after the build) to learn how everything is rendered.

User documentation:

- `reStructuredText Primer <https://docutils.sourceforge.io/docs/user/rst/quickstart.html>`_
- `quick reStructuredText reference <https://docutils.sourceforge.io/docs/user/rst/quickref.html>`_
- `reStructuredText Cheat Sheet <https://docutils.sourceforge.io/docs/user/rst/cheatsheet.txt>`_ (text only)

Reference documentation:

- `reStructuredText Directives`_
- `reStructuredText Markup Specificaton <docutils.sourceforge.io/docs/ref/rst/restructuredtext.html>`_
- `reStructuredText Interpreted Text Roles <https://docutils.sourceforge.io/docs/ref/rst/roles.html>`_

Heading 2
#########

Heading 3
=========

Heading 4
---------

Heading 5
~~~~~~~~~

Heading 6
_________

Unlike Markdown, reStructuredText does not specify exact characters for any heading. It will create smaller headings as long as each further-nested heading uses a different character. **The underline/overline character sequence must be at least as long as the heading text.**

It is recommended to stick to the order presented above for consistency (# - 2, = - 3, - - 4, ~ - 5, _ - 6). There is no ``<h1>`` heading example **because for every page, the generator will automatically prepend such heading with the page title (specified in metadata at the top of the source file)**.

This is a paragraph.

Paragraphs line up at their left
edges, and are normally separated
by blank lines.

Heading 2 again
###############

Lorem Ipsum
===========

**Lorem ipsum dolor sit amet**, consectetur adipiscing elit. Donec a elementum lectus. Sed quis dolor id ipsum interdum lobortis. Mauris ultricies eleifend rhoncus. Nullam nunc turpis, semper elementum risus ut, imperdiet vehicula elit. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Integer quam diam, tempus a malesuada ut, efficitur eu dolor. Phasellus ipsum urna, tincidunt in pellentesque sit amet, tempus ac dolor. Proin sed est ut arcu efficitur tincidunt quis non libero. Nulla imperdiet quam in orci auctor fermentum. Phasellus in mauris lacinia urna convallis cursus. Vivamus eget massa at magna aliquam fermentum.

Don't line-wrap long text manually by inserting line breaks. Enable line wrap in editor and leave wrapping up to the final content reader (eg web browser).

Blockquotes
-----------

Generates ``<blockquote>`` elements. Already covered in CSS.

    Good afternoon, gentlemen. I am a HAL 9000 computer. I became operational at the H.A.L. plant in Urbana, Illinois on the 12th of January 1992. My instructor was Mr. Langley, and he taught me to sing a song. If you’d like to hear it I can sing it for you. - `HAL 9000 <http://en.wikipedia.org/wiki/HAL_9000>`_

Text-level semantics - reST
---------------------------

The *emphasis* example

The **strong emphasis** example

The `interpreted text` example

The ``inline element`` example

The reference_ example

The `phase reference`_ example

The `anonymous phase reference`__ example

|RST|_ is a little annoying to type over and over, especially
when writing about |RST| itself, and spelling out the
bicapitalized word |RST| every time isn't really necessary for
|RST| source readability.

The footnote reference [101]_ example

The citation reference [CIT2020]_ example

The https://docutils.sourceforge.io/docs/user/rst/quickref.html example

.. _reference: something to be referenced here
.. _phase reference: here it can contain spaces
__ whatever here, in order of the anonymous references in the content
.. |RST| replace:: reStructuredText
.. _RST: http://docutils.sourceforge.net/rst.html
.. [101] note the lack of colon in footnote definition
.. [CIT2020] same here

**Inline markup may not be nested.** If you find that you want to use one of the "special" characters in text, it will generally be OK -- reStructuredText is pretty smart. For example, this lone asterisk * is handled just fine, as is the asterisk in this equation: 5*6=30. If you actually want text *surrounded by asterisks* to not be italicised, then you need to indicate that the asterisk is not special. You do this by placing a backslash just before it, like so "\*". Inline markup by itself (surrounded by whitespace) or in the middle of a word won't be recognized - it has to be escaped like in the following sentence:

Possible in *re*\ ``Structured``\ *Text*, though not encouraged.

*escape* ``with`` "\"

\*escape* \``with`` "\\"

Text-level semantics - HTML in reST
-----------------------------------

The <abbr>abbr element</abbr> and <abbr title="Title text">abbr element with title</abbr> examples

The <cite>cite element</cite> example

The <del>del element</del> example

The <dfn>dfn element</dfn> and <dfn title="Title text">dfn element with title</dfn> examples

The <ins>ins element</ins> example

The <kbd>kbd element</kbd> example

The <mark>mark element</mark> example

The <q>q element <q>inside</q> a q element</q> example

The <s>s element</s> example

The <samp>samp element</samp> example

The <small>small element</small> example

The <span>span element</span> example

The <sub>sub element</sub> example

The <sup>sup element</sup> example

The <var>var element</var> example

The <u>u element</u> example

Lists
=====

Bullet lists:
- This is item 1
- This is item 2

- Bullets are "-", "*" or "+".
  Continuing text must be aligned
  after the bullet and whitespace.

Note that a blank line is required
before the first item and after the
last, but is optional between items.

Enumerated lists:

3. This is the first item
4. This is the second item
5. Enumerators are arabic numbers,
   single letters, or roman numerals
6. List items should be sequentially
   numbered, but need not start at 1
   (although not all formatters will
   honour the first index).
#. This item is auto-enumerated

Definition lists:

what
  Definition lists associate a term with
  a definition.

how
  The term is a one-line phrase, and the
  definition is one or more paragraphs or
  body elements, indented relative to the
  term. Blank lines are not allowed
  between term and definition.

Field Lists
===========

:Authors:
    Tony J. (Tibs) Ibbs,
    David Goodger
    (and sundry other good-natured folks)

:Version: 1.0 of 2001/08/08
:Dedication: To my father.

Option Lists
============

There must be at least two spaces between the option and the description.

-a            command-line option "a"
-b file       options can have arguments
              and long descriptions
--long        options can be long also
--input=file  long options can also have
              arguments
/V            DOS/VMS-style options too

Literal Blocks
==============

A paragraph containing only two colons
indicates that the following indented
or quoted text is a literal block.

::

  Whitespace, newlines, blank lines, and
  all kinds of markup (like *this* or
  \this) is preserved by literal blocks.

  The paragraph containing only '::'
  will be omitted from the result.

The ``::`` may be tacked onto the very
end of any paragraph. The ``::`` will be
omitted if it is preceded by whitespace.
The ``::`` will be converted to a single
colon if preceded by text, like this::

  It's very convenient to use this form.

Literal blocks end when text returns to
the preceding paragraph's indentation.
This means that something like this
is possible::

      We start here
    and continue here
  and end here.

Per-line quoting can also be used on
unindented literal blocks::

> Useful for quotes from email and
> for Haskell literate programming.

Line Blocks
===========

| Line blocks are useful for addresses,
| verse, and adornment-free lists.
|
| Each new line begins with a
| vertical bar ("|").
|     Line breaks and initial indents
|     are preserved.
| Continuation lines are wrapped
  portions of long lines; they begin
  with spaces in place of vertical bars.

Block Quotes
============

Block quotes are just:

    Indented paragraphs,

        and they may nest.

Doctest Blocks
==============

Doctest blocks are interactive
Python sessions. They begin with
"``>>>``" and end with a blank line.

>>> print "This is a doctest block."
This is a doctest block.

Tables
======

There are two syntaxes for tables in reStructuredText. Grid tables are complete but cumbersome to create. Simple tables are easy to create but limited (no row spans, etc.).

Grid table:

+------------+------------+-----------+
| Header 1   | Header 2   | Header 3  |
+============+============+===========+
| body row 1 | column 2   | column 3  |
+------------+------------+-----------+
| body row 2 | Cells may span columns.|
+------------+------------+-----------+
| body row 3 | Cells may  | - Cells   |
+------------+ span rows. | - contain |
| body row 4 |            | - blocks. |
+------------+------------+-----------+

Simple table:

=====  =====  ======
   Inputs     Output
------------  ------
  A      B    A or B
=====  =====  ======
False  False  False
True   False  True
False  True   True
True   True   True
=====  =====  ======

Transitions
===========

Transitions are commonly seen in novels and short fiction, as a gap spanning one or more lines, marking text divisions or signaling changes in subject, time, point of view, or emphasis.

A transition marker is a horizontal line
of 4 or more repeated punctuation
characters.

------------

A transition should not begin or end a
section or document, nor should two
transitions be immediately adjacent.

Explicit Markup
===============

Explicit markup blocks are used for constructs which float (footnotes), have no direct paper-document representation (hyperlink targets, comments), or require specialized processing (directives). They all begin with two periods and whitespace, the "explicit markup start".

The numbering of auto-numbered footnotes is determined by the order of the footnotes, not of the references. For auto-numbered footnote references without autonumber labels (``[#]_``), the references and footnotes must be in the same relative order. Similarly for auto-symbol footnotes (``[*]_``).

Example 1
---------

Footnote references, like [5]_.
Note that footnotes may get
rearranged, e.g., to the bottom of
the "page".

.. [5] A numerical footnote. Note
   there's no colon after the ``]``.

Example 2
---------

Autonumbered footnotes are
possible, like using [#]_ and [#]_.

.. [#] This is the first one.
.. [#] This is the second one.

They may be assigned 'autonumber
labels' - for instance,
[#fourth]_ and [#third]_.

.. [#third] a.k.a. third_
.. [#fourth] a.k.a. fourth_

Example 3
---------

Auto-symbol footnotes are also
possible, like this: [*]_ and [*]_.

.. [*] This is the first one.
.. [*] This is the second one.

Citations
=========

Citation references, like [CIT2002]_.
Note that citations may get
rearranged, e.g., to the bottom of
the "page".

.. [CIT2002] A citation
   (as often used in journals).

Citation labels contain alphanumerics,
underlines, hyphens and fullstops.
Case is not significant.

Given a citation like [this]_, one
can also refer to it like this_.

.. [this] here.

Hyperlink Targets
=================

External Hyperlink Targets
--------------------------

External hyperlinks, like Python_.

.. _Python: http://www.python.org/

Embedded URIs
~~~~~~~~~~~~~

External hyperlinks, like `Python
<http://www.python.org/>`_.

Internal Hyperlink Targets
--------------------------

Internal crossreferences, like example_.

.. _example:

This is an example crossreference target.

Indirect Hyperlink Targets
--------------------------

The second hyperlink target (the line beginning with "__") is both an indirect hyperlink target (*indirectly* pointing at the Python website via the "Python_" reference) and an **anonymous hyperlink target**. In the text, a double-underscore suffix is used to indicate an **anonymous hyperlink reference**. In an anonymous hyperlink target, the reference text is not repeated. This is useful for references with long text or throw-away references, but the target should be kept close to the reference to prevent them going out of sync.

Python_ is `my favourite
programming language`__.

.. _Python: http://www.python.org/

__ Python_

Implicit Hyperlink Targets
--------------------------

Section titles, footnotes, and citations automatically generate hyperlink targets (the title text or footnote/citation label is used as the hyperlink name).

Implict references, like `Heading 2`_ are automatically linked.

Directives
==========

Directives are a general-purpose extension mechanism, a way of adding support for new constructs without adding new syntax. For a description of all standard directives, see `reStructuredText Directives`_.

.. _reStructuredText Directives: https://docutils.sourceforge.io/docs/ref/rst/directives.html

.. image:: http://placehold.it/800x400
   :alt: large example image

.. image:: http://placehold.it/400x200
   :alt: medium example image

.. image:: http://placehold.it/200x200
   :alt: small example image

Substitution References and Definitions
---------------------------------------

Substitutions are like inline directives, allowing graphics and arbitrary constructs within text.

The |biohazard| symbol must be used on containers used to dispose of medical waste. And here is a fancy jumping ball: |ball|.

.. |biohazard| image:: https://docutils.sourceforge.io/docs/user/rst/images/biohazard.png
.. |ball| image:: https://docutils.sourceforge.io/docs/user/rst/images/ball1.gif

Comments
========

Any text which begins with an explicit markup start but doesn't use the syntax of any of the constructs above, is a comment.

.. This text will not be shown
   (but, for instance, in HTML might be
   rendered as an HTML comment)

An "empty comment" does not
consume following blocks.
(An empty comment is ".." with
blank lines before and after.)

..

        So this block is not "lost",
        despite its indentation.

More advanced directives
========================

Admonitions
-----------

Predefined Admonitions
~~~~~~~~~~~~~~~~~~~~~~

.. danger::
   Beware killer rabbits!

.. attention::
   You need to learn the syntax before writing code.

.. caution::
   You better read the docs before resolving to trial and error.

.. error::
   An error occured while displaying previous error.

.. hint::
   Something that the IDE should do often to make writing code easier.

.. important::
   Enable warnings when compiling any code.

.. note::
   There is also a custom admonition.

.. tip::
   2 days of debugging can save you 5 minutes of reading the documentation.

.. warning::
   Unused variable.

Custom Admonition
~~~~~~~~~~~~~~~~~

.. admonition:: And, by the way...
   :class: my-admonition-class

   You can make up your own admonition too. With specified class.

.. admonition:: Congratulations!
   :class: success

   You have finished the easy-mode Python tutorial. Now complete the inferno difficulty by changing the language to C++ or Java Script.

.. admonition:: One Definition Rule
   :class: definition

   There should be at most one definition of One Definition Rule on this page.

Images
------

Image
~~~~~

An "image" is a simple picture:

.. image:: picture.png

Inline images can be defined with an "image" directive in a substitution definition

The URI for the image source file is specified in the directive argument. As with hyperlink targets, the image URI may begin on the same line as the explicit markup start and target name, or it may begin in an indented text block immediately following, with no intervening blank lines. If there are multiple lines in the link block, they are stripped of leading and trailing whitespace and joined together.

Optionally, the image link block may contain a flat field list, the image options. For example:

.. image:: picture.jpeg
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right

The following options are recognized:

``alt`` : text
    Alternate text: a short description of the image, displayed by
    applications that cannot display images, or spoken by applications
    for visually impaired users.

``height`` : *length*
    The desired height of the image.
    Used to reserve space or scale the image vertically.  When the "scale"
    option is also specified, they are combined.  For example, a height of
    200px and a scale of 50 is equivalent to a height of 100px with no scale.

``width`` : *length* or *percentage* of the current line width
    The width of the image.
    Used to reserve space or scale the image horizontally.  As with "height"
    above, when the "scale" option is also specified, they are combined.

``scale`` : integer percentage (the "%" symbol is optional)
    The uniform scaling factor of the image.  The default is "100Â %", i.e.
    no scaling.

    If no "height" or "width" options are specified, the *Python Imaging
    Library* (PIL) may be used to determine them, if it is installed and
    the image file is available.

``align`` : "top", "middle", "bottom", "left", "center", or "right"
    The alignment of the image, equivalent to the HTML ``<img>`` tag's
    deprecated "align" attribute or the corresponding "vertical-align" and
    "text-align" CSS properties.
    The values "top", "middle", and "bottom"
    control an image's vertical alignment (relative to the text
    baseline); they are only useful for inline images (substitutions).
    The values "left", "center", and "right" control an image's
    horizontal alignment, allowing the image to float and have the
    text flow around it.  The specific behavior depends upon the
    browser or rendering software used.

``target`` : text (URI or reference name)
    Makes the image into a hyperlink reference ("clickable").  The
    option argument may be a URI (relative or absolute), or a
    *reference name* with underscore suffix (e.g. ```a name`_``).

and the common options ``:class:`` and ``:name:``.

Figure
~~~~~~

A "figure" consists of image data (including image options), an optional caption (a single paragraph), and an optional legend (arbitrary body elements). For page-based output media, figures might float to a different position if this helps the page layout.

.. figure:: picture.png
   :scale: 50 %
   :alt: map to buried treasure

   This is the caption of the figure (a simple paragraph).

   The legend consists of all elements after the caption.  In this
   case, the legend consists of this paragraph and the following
   table:

   +-----------------------+-----------------------+
   | Symbol                | Meaning               |
   +=======================+=======================+
   | .. image:: tent.png   | Campground            |
   +-----------------------+-----------------------+
   | .. image:: waves.png  | Lake                  |
   +-----------------------+-----------------------+
   | .. image:: peak.png   | Mountain              |
   +-----------------------+-----------------------+

Body Elements
-------------

Topic
~~~~~

A topic is like a block quote with a title, or a self-contained section with no subsections. Use the "topic" directive to indicate a self-contained idea that is separate from the flow of the document. Topics may occur anywhere a section or transition may occur. Body elements and topics may not contain nested topics.

The directive's sole argument is interpreted as the topic title; the next line must be blank. All subsequent lines make up the topic body, interpreted as body elements. For example:

.. topic:: Topic Title

    Subsequent indented lines comprise
    the body of the topic, and are
    interpreted as body elements.

Sidebar
~~~~~~~

Sidebars are like miniature, parallel documents that occur inside other documents, providing related or reference material. A sidebar is typically offset by a border and "floats" to the side of the page; the document's main text may flow around it. Sidebars can also be likened to super-footnotes; their content is outside of the flow of the document's main text.

Sidebars may occur anywhere a section or transition may occur. Body elements (including sidebars) may not contain nested sidebars.

The directive's sole argument is interpreted as the sidebar title, which may be followed by a subtitle option (see below); the next line must be blank. All subsequent lines make up the sidebar body, interpreted as body elements. For example:

.. sidebar:: Sidebar Title
   :subtitle: Optional Sidebar Subtitle

   Subsequent indented lines comprise
   the body of the sidebar, and are
   interpreted as body elements.

Parsed Literal Block
~~~~~~~~~~~~~~~~~~~~

Unlike an ordinary literal block, the "parsed-literal" directive constructs a literal block where the text is parsed for inline markup. It is equivalent to a line block with different rendering: typically in a typewriter/monospaced typeface, like an ordinary literal block. Parsed literal blocks are useful for adding hyperlinks to code examples.

However, care must be taken with the text, because inline markup is recognized and there is no protection from parsing. Backslash-escapes may be necessary to prevent unintended parsing. And because the markup characters are removed by the parser, care must also be taken with vertical alignment. Parsed "ASCII art" is tricky, and extra whitespace may be necessary.

For example, all the element names in this content model are links:

.. parsed-literal::

   ( (title_, subtitle_?)?,
     decoration_?,
     (docinfo_, transition_?)?,
     `%structure.model;`_ )

.. _title: title here
.. _subtitle: subtitle here
.. _decoration: decoration here
.. _docinfo: docinfo here
.. _transition: transition here
.. _`%structure.model;`: structure model here

Code
~~~~

The "code" directive constructs a literal block. If the code language is specified, the content is parsed by the Pygments syntax highlighter and tokens are stored in nested inline elements with class arguments according to their syntactic category. The actual highlighting requires a style-sheet (e.g. one generated by Pygments, see the sandbox/stylesheets for examples).

The parsing can be turned off with the syntax_highlight configuration setting and command line option or by specifying the language as ``:class:`` option instead of directive argument. This also avoids warnings when Pygments is not installed or the language is not in the supported languages and markup formats.

.. code:: python
   :number-lines:

   def my_function():
       "just a test"
       print 8/2

Math
~~~~

The "math" directive inserts blocks with mathematical content (display formulas, equations) into the document. The input format is LaTeX math syntax [#]_ with support for Unicode symbols, for example:

.. math::

   α_t(i) = P(O_1, O_2, … O_t, q_t = S_i λ)


Support is limited to a subset of LaTeX math by the conversion required for many output formats. For HTML, the math_output configuration setting (or the corresponding ``--math-output`` command line option) select between alternative output formats with different subsets of supported elements. If a writer does not support math typesetting at all, the content is inserted verbatim.

.. [#] The supported LaTeX commands include AMS extensions (see, e.g., the Short Math Guide).

Epigraph
~~~~~~~~

An epigraph is an apposite (suitable, apt, or pertinent) short inscription, often a quotation or poem, at the beginning of a document or section.

The "epigraph" directive produces an "epigraph"-class block quote. For example, this input:

.. epigraph::

   No matter where you go, there you are.

   -- Buckaroo Banzai

Highlights
~~~~~~~~~~

Highlights summarize the main points of a document or section, often consisting of a list.

The "highlights" directive produces a "highlights"-class block quote.

.. highlights::

   No matter where you go, there you are.

   -- Buckaroo Banzai

Pull-Quote
~~~~~~~~~~

A pull-quote is a small selection of text "pulled out and quoted", typically in a larger typeface. Pull-quotes are used to attract attention, especially in long articles.

The "pull-quote" directive produces a "pull-quote"-class block quote.

.. pull-quote::

   No matter where you go, there you are.

Compound Paragraph
~~~~~~~~~~~~~~~~~~

The "compound" directive is used to create a compound paragraph, which is a single logical paragraph containing multiple physical body elements such as simple paragraphs, literal blocks, tables, lists, etc., instead of directly containing text and inline elements. For example:

.. compound::

   The 'rm' command is very dangerous.  If you are logged
   in as root and enter ::

       cd /
       rm -rf *

   you will erase the entire contents of your file system.

In the example above, a literal block is "embedded" within a sentence that begins in one physical paragraph and ends in another.

The "compound" directive is not a generic block-level container like HTML's ``<div>`` element. Do not use it only to group a sequence of elements, or you may get unexpected results.

If you need a generic block-level container, use the container directive.

Compound paragraphs are typically rendered as multiple distinct text blocks, with the possibility of variations to emphasize their logical unity:

- If paragraphs are rendered with a first-line indent, only the first physical paragraph of a compound paragraph should have that indent -- second and further physical paragraphs should omit the indents;
- vertical spacing between physical elements may be reduced;
- and so on.

Container
~~~~~~~~~

The "container" directive surrounds its contents (arbitrary body elements) with a generic block-level "container" element. Combined with the optional "classes" attribute argument(s), this is an extension mechanism for users & applications. For example:

.. container:: custom

   This paragraph might be rendered in a custom way.

The "container" directive is the equivalent of HTML's ``<div>`` element. It may be used to group a sequence of elements for user- or application-specific purposes.

Tables
------

Table
~~~~~

The "table" directive is used to associate a title with a table or specify options, e.g.:

.. table:: Truth table for "not"
   :widths: auto

   =====  =====
     A    not A
   =====  =====
   False  True
   True   False
   =====  =====

The following options are recognized:

``align`` : "left", "center", or "right"
    The horizontal alignment of the table.
    (New in Docutils 0.13)

``widths`` : "auto", "grid" or a list of integers
    A comma- or space-separated list of column widths.
    The default is the width of the input columns (in characters).

    The special values "auto" or "grid" may be used by writers to decide
    whether to delegate the determination of column widths to the backend
    (LaTeX, the HTML browser, ...).
    See also the *table_style* configuration option.

``width`` : *length* or *percentage* of the current line width
    Forces the width of the table to the specified length or percentage
    of the line width.  If omitted, the renderer determines the width
    of the table based on its contents.

and the common options ``:class:`` and ``:name:``.

CSV Table
~~~~~~~~~

The "csv-table" directive is used to create a table from CSV (comma-separated values) data. CSV is a common data format generated by spreadsheet applications and commercial databases. The data may be internal (an integral part of the document) or external (a separate file).

Example:

.. csv-table:: Frozen Delights!
   :header: "Treat", "Quantity", "Description"
   :widths: 15, 10, 30

   "Albatross", 2.99, "On a stick!"
   "Crunchy Frog", 1.49, "If we took the bones out, it wouldn't be
   crunchy, now would it?"
   "Gannet Ripple", 1.99, "On a stick!"

Block markup and inline markup within cells is supported. Line ends are recognized within cells.

Working limitations:

- There is no support for checking that the number of columns in each row is the same.  However, this directive supports CSV generators that do not insert "empty" entries at the end of short rows, by automatically adding empty entries.
- Whitespace delimiters are supported only for external CSV files.
- With PythonÂ 2, the valuess for the ``delimiter``, ``quote``, and ``escape`` options must be ASCII characters. (The csv module does not support Unicode and all non-ASCII characters are encoded as multi-byte utf-8 string). This limitation does not exist under PythonÂ 3.

The following options are recognized:

``widths`` : integer [, integer...] or "auto"
    A comma- or space-separated list of relative column widths.  The
    default is equal-width columns (100%/#columns).

    The special value "auto" may be used by writers to decide
    whether to delegate the determination of column widths to the backend
    (LaTeX, the HTML browser, ...).

``width`` : *length* or *percentage* of the current line width
    Forces the width of the table to the specified length or percentage
    of the line width.  If omitted, the renderer determines the width
    of the table based on its contents.

``header-rows`` : integer
    The number of rows of CSV data to use in the table header.
    Defaults to 0.

``stub-columns`` : integer
    The number of table columns to use as stubs (row titles, on the
    left).  Defaults to 0.

``header`` : CSV data
    Supplemental data for the table header, added independently of and
    before any ``header-rows`` from the main CSV data.  Must use the
    same CSV format as the main CSV data.

``file`` : string (newlines removed)
    The local filesystem path to a CSV data file.

``url`` : string (whitespace removed)
    An Internet URL reference to a CSV data file.

``encoding`` : name of text encoding
    The text encoding of the external CSV data (file or URL).
    Defaults to the document's encoding (if specified).

``delim`` : char | "tab" | "space"
    A one-character string used to separate fields.
    Defaults to ``,`` (comma).  May be specified as a Unicode code
    point; see the *unicode* directive for syntax details.

``quote`` : char
    A one-character string used to quote elements
    containing the delimiter or which start with the quote
    character.  Defaults to ``"`` (quote).  May be specified as a
    Unicode code point; see the *unicode* directive for syntax
    details.

``keepspace`` : flag
    Treat whitespace immediately following the delimiter as
    significant.  The default is to ignore such whitespace.

``escape`` : char
    A one-character string used to escape the
    delimiter or quote characters.  May be specified as a Unicode
    code point; see the *unicode* directive for syntax details.  Used
    when the delimiter is used in an unquoted field, or when quote
    characters are used within a field.  The default is to double-up
    the character, e.g. "He said, ""Hi!"""

    .. Add another possible value, "double", to explicitly indicate
       the default case?

``align`` : "left", "center", or "right"
    The horizontal alignment of the table.
    (New in Docutils 0.13)

and the common options ``:class:`` and ``:name:``.

List Table
~~~~~~~~~~

The "list-table" directive is used to create a table from data in a uniform two-level bullet list. "Uniform" means that each sublist (second-level list) must contain the same number of list items.

.. list-table:: Frozen Delights!
   :widths: 15 10 30
   :header-rows: 1

   * - Treat
     - Quantity
     - Description
   * - Albatross
     - 2.99
     - On a stick!
   * - Crunchy Frog
     - 1.49
     - If we took the bones out, it wouldn't be
       crunchy, now would it?
   * - Gannet Ripple
     - 1.99
     - On a stick!

The following options are recognized:

``widths`` : integer [integer...] or "auto"
    A comma- or space-separated list of relative column widths.  The
    default is equal-width columns (100%/#columns).

    The special value "auto" may be used by writers to decide
    whether to delegate the determination of column widths to the backend
    (LaTeX, the HTML browser, ...).

``width`` : *length* or *percentage* of the current line width
    Forces the width of the table to the specified length or percentage
    of the line width.  If omitted, the renderer determines the width
    of the table based on its contents.

``header-rows`` : integer
    The number of rows of list data to use in the table header.
    Defaults to 0.

``stub-columns`` : integer
    The number of table columns to use as stubs (row titles, on the
    left).  Defaults to 0.

``align`` : "left", "center", or "right"
    The horizontal alignment of the table.
    (New in Docutils 0.13)

and the common options ``:class:`` and ``:name:``.

Document Parts
--------------

Table of Contents
~~~~~~~~~~~~~~~~~

Here's the directive in its simplest form::

    .. contents::

Language-dependent boilerplate text will be used for the title.  The
English default title text is "Contents".

An explicit title may be specified::

    .. contents:: Table of Contents

The title may span lines, although it is not recommended::

    .. contents:: Here's a very long Table of
       Contents title

Options may be specified for the directive, using a field list::

    .. contents:: Table of Contents
       :depth: 2

If the default title is to be used, the options field list may begin
on the same line as the directive marker::

    .. contents:: :depth: 2

The following options are recognized:

``depth`` : integer
    The number of section levels that are collected in the table of
    contents.  The default is unlimited depth.

``local`` : flag (empty)
    Generate a local table of contents.  Entries will only include
    subsections of the section in which the directive is given.  If no
    explicit title is given, the table of contents will not be titled.

``backlinks`` : "entry" or "top" or "none"
    Generate links from section headers back to the table of contents
    entries, the table of contents itself, or generate no backlinks.

``class`` : text
    Set a "classes" attribute value on the topic element.

Automatic Section Numbering
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The "sectnum" (or "section-numbering") directive automatically numbers
sections and subsections in a document (if not disabled by the
``--no-section-numbering`` command line option or the *sectnum_xform*
configuration setting).

Section numbers are of the "multiple enumeration" form, where each
level has a number, separated by periods.  For example, the title of section
1, subsection 2, subsubsection 3 would have "1.2.3" prefixed.

The "sectnum" directive does its work in two passes: the initial parse
and a transform.  During the initial parse, a "pending" element is
generated which acts as a placeholder, storing any options internally.
At a later stage in the processing, the "pending" element triggers a
transform, which adds section numbers to titles.  Section numbers are
enclosed in a "generated" element, and titles have their "auto"
attribute set to "1".

The following options are recognized:

``depth`` : integer
    The number of section levels that are numbered by this directive.
    The default is unlimited depth.

``prefix`` : string
    An arbitrary string that is prefixed to the automatically
    generated section numbers.  It may be something like "3.2.", which
    will produce "3.2.1", "3.2.2", "3.2.2.1", and so on.  Note that
    any separating punctuation (in the example, a period, ".") must be
    explicitly provided.  The default is no prefix.

``suffix`` : string
    An arbitrary string that is appended to the automatically
    generated section numbers.  The default is no suffix.

``start`` : integer
    The value that will be used for the first section number.
    Combined with ``prefix``, this may be used to force the right
    numbering for a document split over several source files.  The
    default is 1.

Document Header & Footer
~~~~~~~~~~~~~~~~~~~~~~~~

The "header" and "footer" directives create document decorations,
useful for page navigation, notes, time/datestamp, etc.  For example::

    .. header:: This space for rent.

This will add a paragraph to the document header, which will appear at
the top of the generated web page or at the top of every printed page.

These directives may be used multiple times, cumulatively.  There is
currently support for only one header and footer.

.. note::

   While it is possible to use the "header" and "footer" directives to
   create navigational elements for web pages, you should be aware
   that Docutils is meant to be used for *document* processing, and
   that a navigation bar is not typically part of a document.

   Thus, you may soon find Docutils' abilities to be insufficient for
   these purposes.  At that time, you should consider using a
   documentation generator like Sphinx_ rather than the "header" and
   "footer" directives.

   .. _Sphinx: http://sphinx-doc.org/

In addition to the use of these directives to populate header and
footer content, content may also be added automatically by the
processing system.  For example, if certain runtime settings are
enabled, the document footer is populated with processing information
such as a datestamp, a link to `the Docutils website`_, etc.

.. _the Docutils website: http://docutils.sourceforge.net

References
----------

Target Footnotes
~~~~~~~~~~~~~~~~

The "target-notes" directive creates a footnote for each external
target in the text, and corresponding footnote references after each
reference.  For every explicit target (of the form, ``.. _target name:
URL``) in the text, a footnote will be generated containing the
visible URL as content.

Footnotes
~~~~~~~~~

**NOT IMPLEMENTED YET** by docutils.

Citations
~~~~~~~~~

**NOT IMPLEMENTED YET** by docutils.

HTML-Specific
-------------

Meta
~~~~

The "meta" directive is used to specify HTML metadata stored in HTML
META tags.  "Metadata" is data about data, in this case data about web
pages.  Metadata is used to describe and classify web pages in the
World Wide Web, in a form that is easy for search engines to extract
and collate.

Within the directive block, a flat field list provides the syntax for
metadata.  The field name becomes the contents of the "name" attribute
of the META tag, and the field body (interpreted as a single string
without inline markup) becomes the contents of the "content"
attribute.  For example::

    .. meta::
       :description: The reStructuredText plaintext markup language
       :keywords: plaintext, markup language

This would be converted to the following HTML::

    <meta name="description"
        content="The reStructuredText plaintext markup language">
    <meta name="keywords" content="plaintext, markup language">

Support for other META attributes ("http-equiv", "scheme", "lang",
"dir") are provided through field arguments, which must be of the form
"attr=value"::

    .. meta::
       :description lang=en: An amusing story
       :description lang=fr: Une histoire amusante

And their HTML equivalents::

    <meta name="description" lang="en" content="An amusing story">
    <meta name="description" lang="fr" content="Une histoire amusante">

Some META tags use an "http-equiv" attribute instead of the "name"
attribute.  To specify "http-equiv" META tags, simply omit the name::

    .. meta::
       :http-equiv=Content-Type: text/html; charset=ISO-8859-1

HTML equivalent::

    <meta http-equiv="Content-Type"
         content="text/html; charset=ISO-8859-1">


Imagemap
~~~~~~~~

**NOT IMPLEMENTED YET** by docutils.

Non-standard element: imagemap.

Directives for Substitution Definitions
---------------------------------------

The directives in this section may only be used in substitution definitions. They may not be used directly, in standalone context. The image directive may be used both in substitution definitions and in the standalone context.

Replacement Text
~~~~~~~~~~~~~~~~

The "replace" directive is used to indicate replacement text for a substitution reference. It may be used within substitution definitions only. For example, this directive can be used to expand abbreviations:

.. |reST| replace:: reStructuredText

Yes, |reST| is a long word, so I can't blame anyone for wanting to
abbreviate it.
As reStructuredText doesn't support nested inline markup, the only way to create a reference with styled text is to use substitutions with the "replace" directive:

I recommend you try |Python|_.

.. |Python| replace:: Python, *the* best language around
.. _Python: http://www.python.org/

Unicode Character Codes
~~~~~~~~~~~~~~~~~~~~~~~

The "unicode" directive converts Unicode character codes (numerical
values) to characters, and may be used in substitution definitions
only.

The arguments, separated by spaces, can be:

* **character codes** as

  - decimal numbers or

  - hexadecimal numbers, prefixed by ``0x``, ``x``, ``\x``, ``U+``,
    ``u``, or ``\u`` or as XML-style hexadecimal character entities,
    e.g. ``&#x1a2b;``

* **text**, which is used as-is.

Text following " .. " is a comment and is ignored.  The spaces between
the arguments are ignored and thus do not appear in the output.
Hexadecimal codes are case-insensitive.

For example, the following text::

    Copyright |copy| 2003, |BogusMegaCorp (TM)| |---|
    all rights reserved.

    .. |copy| unicode:: 0xA9 .. copyright sign
    .. |BogusMegaCorp (TM)| unicode:: BogusMegaCorp U+2122
       .. with trademark sign
    .. |---| unicode:: U+02014 .. em dash
       :trim:

results in:

    Copyright |copy| 2003, |BogusMegaCorp (TM)| |---|
    all rights reserved.

    .. |copy| unicode:: 0xA9 .. copyright sign
    .. |BogusMegaCorp (TM)| unicode:: BogusMegaCorp U+2122
       .. with trademark sign
    .. |---| unicode:: U+02014 .. em dash
       :trim:

The following options are recognized:

``ltrim`` : flag
    Whitespace to the left of the substitution reference is removed.

``rtrim`` : flag
    Whitespace to the right of the substitution reference is removed.

``trim`` : flag
    Equivalent to ``ltrim`` plus ``rtrim``; whitespace on both sides
    of the substitution reference is removed.

Date
~~~~

The "date" directive generates the current local date and inserts it
into the document as text.  This directive may be used in substitution
definitions only.

The optional directive content is interpreted as the desired date
format, using the same codes as Python's time.strftime function.  The
default format is "%Y-%m-%d" (ISO 8601 date), but time fields can also
be used.  Examples::

    .. |date| date::
    .. |time| date:: %H:%M

    Today's date is |date|.

    This document was generated on |date| at |time|.

Miscellaneous
-------------

Including an External Document Fragment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The "include" directive reads a text file. The directive argument is
the path to the file to be included, relative to the document
containing the directive. Unless the options ``literal`` or ``code``
are given, the file is parsed in the current document's context at the
point of the directive. For example::

    This first example will be parsed at the document level, and can
    thus contain any construct, including section headers.

    .. include:: inclusion.txt

    Back in the main document.

        This second example will be parsed in a block quote context.
        Therefore it may only contain body elements.  It may not
        contain section headers.

        .. include:: inclusion.txt

If an included document fragment contains section structure, the title
adornments must match those of the master document.

Standard data files intended for inclusion in reStructuredText
documents are distributed with the Docutils source code, located in
the "docutils" package in the ``docutils/parsers/rst/include``
directory.  To access these files, use the special syntax for standard
"include" data files, angle brackets around the file name::

    .. include:: <isonum.txt>

The current set of standard "include" data files consists of sets of
substitution definitions.  See `reStructuredText Standard Definition
Files`__ for details.

__ https://docutils.sourceforge.io/docs/ref/rst/definitions.html

The following options are recognized:

``start-line`` : integer
    Only the content starting from this line will be included.
    (As usual in Python, the first line has index 0 and negative values
    count from the end.)

``end-line`` : integer
    Only the content up to (but excluding) this line will be included.

``start-after`` : text to find in the external data file
    Only the content after the first occurrence of the specified text
    will be included.

``end-before`` : text to find in the external data file
    Only the content before the first occurrence of the specified text
    (but after any ``after`` text) will be included.

``literal`` : flag (empty)
    The entire included text is inserted into the document as a single
    literal block.

``code`` : formal language (optional)
    The argument and the content of the included file are passed to
    the code_ directive (useful for program listings).
    (New in Docutils 0.9)

``number-lines`` : [start line number]
    Precede every code line with a line number.
    The optional argument is the number of the first line (defaut 1).
    Works only with ``code`` or ``literal``.
    (New in Docutils 0.9)

``encoding`` : name of text encoding
    The text encoding of the external data file.  Defaults to the
    document's input_encoding_.

    .. _input_encoding: https://docutils.sourceforge.io/docs/user/config.html#input-encoding

``tab-width`` :  integer
    Number of spaces for hard tab expansion.
    A negative value prevents expansion of hard tabs. Defaults to the
    tab_width_ configuration setting.

    .. _tab_width: https://docutils.sourceforge.io/docs/user/config.html#tab-width


With ``code`` or ``literal`` the common options ``:class:`` and
``:name:`` are recognized as well.

Combining ``start/end-line`` and ``start-after/end-before`` is possible. The text markers will be searched in the specified lines (further limiting the included content).

Raw Data Pass-Through
~~~~~~~~~~~~~~~~~~~~~

.. Caution::

   The "raw" directive is a stop-gap measure allowing the author to
   bypass reStructuredText's markup.  It is a "power-user" feature
   that should not be overused or abused.  The use of "raw" ties
   documents to specific output formats and makes them less portable.

   If you often need to use the "raw" directive or a "raw"-derived
   interpreted text role, that is a sign either of overuse/abuse or
   that functionality may be missing from reStructuredText.  Please
   describe your situation in a message to the Docutils-users_ mailing
   list.

.. _Docutils-users: https://docutils.sourceforge.io/docs/user/mailing-lists.html#docutils-users

The "raw" directive indicates non-reStructuredText data that is to be
passed untouched to the Writer.  The names of the output formats are
given in the directive arguments.  The interpretation of the raw data
is up to the Writer.  A Writer may ignore any raw output not matching
its format.

For example, the following input would be passed untouched by an HTML
Writer::

    .. raw:: html

       <hr width=50 size=10>

A LaTeX Writer could insert the following raw content into its
output stream::

    .. raw:: latex

       \setlength{\parindent}{0pt}

Raw data can also be read from an external file, specified in a
directive option.  In this case, the content block must be empty.  For
example::

    .. raw:: html
       :file: inclusion.html

Inline equivalents of the "raw" directive can be defined via
`custom interpreted text roles <https://docutils.sourceforge.io/docs/ref/rst/directives.html#custom-interpreted-text-roles>`_ derived from the `"raw" role <https://docutils.sourceforge.io/docs/ref/rst/roles.html#raw>`_.

The following options are recognized:

``file`` : string (newlines removed)
    The local filesystem path of a raw data file to be included.

``url`` : string (whitespace removed)
    An Internet URL reference to a raw data file to be included.

``encoding`` : name of text encoding
    The text encoding of the external raw data (file or URL).
    Defaults to the document's encoding (if specified).

Class
~~~~~

The "class" directive sets the `"classes"`_ attribute value on its content
or on the first immediately following [#]_ non-comment element [#]_.
The directive argument consists of one or more space-separated class
names. The names are transformed to conform to the regular expression
``[a-z](-?[a-z0-9]+)*`` (see `Identifier Normalization <https://docutils.sourceforge.io/docs/ref/rst/directives.html#identifier-normalization>`_).

Examples::

    .. class:: special

    This is a "special" paragraph.

    .. class:: exceptional remarkable

    An Exceptional Section
    ======================

    This is an ordinary paragraph.

    .. class:: multiple

       First paragraph.

       Second paragraph.

The text above is parsed and transformed into this doctree fragment::

    <paragraph classes="special">
        This is a "special" paragraph.
    <section classes="exceptional remarkable">
        <title>
            An Exceptional Section
        <paragraph>
            This is an ordinary paragraph.
        <paragraph classes="multiple">
            First paragraph.
        <paragraph classes="multiple">
            Second paragraph.


.. [#] This is also true, if the class directive is "nested" at the end of
   an indented text block, for example::

       .. note:: the class values set in this directive-block do not apply to
          the note but the next paragraph.

          .. class:: special

       This is a paragraph with class value "special".

   This allows the "classification" of individual list items (except the
   first, as a preceding class directive applies to the list as a whole)::

       * bullet list

         .. class:: classy item

       * second item, with class argument

.. [#] To set a "classes" attribute value on a block quote, the
   "class" directive must be followed by an empty comment::

       .. class:: highlights
       ..

           Block quote text.

   Without the empty comment, the indented text would be interpreted as the
   "class" directive's content, and the classes would be applied to each
   element (paragraph, in this case) individually, instead of to the block
   quote as a whole.

Custom Interpreted Text Roles
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The "role" directive dynamically creates a custom interpreted text
role and registers it with the parser.  This means that after
declaring a role like this::

    .. role:: custom

the document may use the new "custom" role::

    An example of using :custom:`interpreted text`

This will be parsed into the following document tree fragment::

    <paragraph>
        An example of using
        <inline classes="custom">
            interpreted text

The role must be declared in a document before it can be used.

The new role may be based on an existing role, specified as a second
argument in parentheses (whitespace optional)::

    .. role:: custom(emphasis)

    :custom:`text`

The parsed result is as follows::

    <paragraph>
        <emphasis classes="custom">
            text

A special case is the `"raw" role <https://docutils.sourceforge.io/docs/ref/rst/roles.html#raw>`_: derived roles enable
inline `raw data pass-through <https://docutils.sourceforge.io/docs/ref/rst/directives.html#raw-data-pass-through>`_, e.g.::

   .. role:: raw-role(raw)
      :format: html latex

   :raw-role:`raw text`

If no base role is explicitly specified, a generic custom role is
automatically used.  Subsequent interpreted text will produce an
"inline" element with a `"classes"`_ attribute, as in the first example
above.

With most roles, the ":class:" option can be used to set a "classes"
attribute that is different from the role name.  For example::

    .. role:: custom
       :class: special

    :custom:`interpreted text`

This is the parsed result::

    <paragraph>
        <inline classes="special">
            interpreted text

.. _role class:

The following option is recognized by the "role" directive for most
base roles:

``class`` : text
    Set the `"classes"`_ attribute value on the element produced
    (``inline``, or element associated with a base class) when the
    custom interpreted text role is used.  If no directive options are
    specified, a "class" option with the directive argument (role
    name) as the value is implied.  See the `class <https://docutils.sourceforge.io/docs/ref/rst/directives.html#class>`_ directive above.

Specific base roles may support other options and/or directive
content.  See the `reStructuredText Interpreted Text Roles <https://docutils.sourceforge.io/docs/ref/rst/roles.html>`_ document
for details.

Setting the Default Interpreted Text Role
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The "default-role" directive sets the default interpreted text role,
the role that is used for interpreted text without an explicit role.
For example, after setting the default role like this::

    .. default-role:: subscript

any subsequent use of implicit-role interpreted text in the document
will use the "subscript" role::

    An example of a `default` role.

This will be parsed into the following document tree fragment::

    <paragraph>
        An example of a
        <subscript>
            default
         role.

Custom roles may be used (see the "role_" directive above), but it
must have been declared in a document before it can be set as the
default role.  See the `reStructuredText Interpreted Text Roles`_
document for details of built-in roles.

The directive may be used without an argument to restore the initial
default interpreted text role, which is application-dependent.  The
initial default interpreted text role of the standard reStructuredText
parser is "title-reference".

Metadata Document Title
~~~~~~~~~~~~~~~~~~~~~~~

The "title" directive specifies the document title as metadata, which does not become part of the document body. It overrides a document-supplied title. For example, in HTML output the metadata document title appears in the title bar of the browser window.

Common Options
==============

Most of the directives that generate doctree elements support the following
options:

.. _class-option:

_`:class:` : text
    Set a `"classes"`_ attribute value on the doctree element generated by
    the directive. See also the class_ directive.

_`:name:` : text
    Add `text` to the `"names"`_ attribute of the doctree element generated
    by the directive. This allows `hyperlink references <https://docutils.sourceforge.io/docs/ref/rst/restructuredtext.html#hyperlink-references>`_ to the element
    using `text` as `reference name <https://docutils.sourceforge.io/docs/ref/rst/restructuredtext.html#reference-names>`_.

    Specifying the `name` option of a directive, e.g., ::

      .. image:: bild.png
         :name: my picture

    is a concise syntax alternative to preceding it with a `hyperlink
    target <https://docutils.sourceforge.io/docs/ref/rst/restructuredtext.html#hyperlink-targets>`_ ::

      .. _my picture:

      .. image:: bild.png

.. _role: https://docutils.sourceforge.io/docs/ref/rst/directives.html#role
.. _`"classes"`: https://docutils.sourceforge.io/docs/ref/doctree.html#classes
.. _`"names"`: https://docutils.sourceforge.io/docs/ref/doctree.html#names
