.. title: reStructuredText examples
.. slug: rest_examples
.. description: reStructuredText examples
.. author: Xeverous

Not all |RST| features have implemented proper HTML/CSS/JS code in this site build process. This page showcases examples of specific |RST| features intended to be used on the website with recommendation how and when to use them.

This page should not be treated as an |RST| learning material. At most as a quick refresher. For learning |RST|, read first:

User documentation:

- `reStructuredText Primer <https://docutils.sourceforge.io/docs/user/rst/quickstart.html>`_
- `quick reStructuredText reference <https://docutils.sourceforge.io/docs/user/rst/quickref.html>`_
- `reStructuredText Cheat Sheet <https://docutils.sourceforge.io/docs/user/rst/cheatsheet.txt>`_ (text only)

Reference documentation:

- `reStructuredText Directives <https://docutils.sourceforge.io/docs/ref/rst/directives.html>`_
- `reStructuredText Markup Specificaton <docutils.sourceforge.io/docs/ref/rst/restructuredtext.html>`_
- `reStructuredText Interpreted Text Roles <https://docutils.sourceforge.io/docs/ref/rst/roles.html>`_

.. Comments are started with *explicit markup start* (..).
.. It's quite complex how/when comments end, so IMO for multiline comments
.. the best approach is to simply start each line with "..".

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

Unlike Markdown, |RST| does not specify exact characters for any heading. It will create smaller headings as long as each further-nested heading uses a different character. **The underline/overline character sequence must be at least as long as the heading text.**

It is recommended to stick to the order presented above for consistency (``#`` - 2, ``=`` - 3, ``-`` - 4, ``~`` - 5, ``_`` - 6). There is no ``<h1>`` heading example **because for every page, the generator will automatically prepend such heading with the page title (specified in metadata at the top of the source file)**.

Examples
########

Paragraphs
==========

Paragraphs are separated by blank lines.

Don't line-wrap long text manually by inserting line breaks. Enable line wrap in editor and leave wrapping up to the final content reader (e.g. web browser). Long text will be rendered in multiple lines, but from the source file point of view it should be on the same line.

Inline markup
=============

By definition, in all inline markups line breaks are not allowed. Inline markup can not be nested.

*italic text* - surround text by ``*``. Use to indicate a term/keyword.

**bold text** - surround text by ``**``. Use to indicate something important.

``literal text`` - surround text by ``````. Use to indicate any form of code.

Interpreted text
----------------

Interpreted text (text surrounded by single `````) is not intended for literal text but for domain- or application-specific meaning. So far there is only 1 use of interpretext text - custom code highlight. Search (unwanted) uses of interpreted text by ``grep -rn "[^\`:]\`[A-Za-z0-9_ ]\+\`[^_\`]" --include="*.rst" website/pages/`` (the only results should be on the |RST| test page).

Custom code highlight: :cch:`std::string::npos`. This works due to ``rest_highlighter`` plugin. The code must be defined in ``data/inline_codes.cpp`` and its highlight in ``data/inline_codes.color``, matching line number. The code need not to be C++, the source file has just ``cpp`` extension for better editor support.

Inline markup - escaping
========================

If you find that you want to use one of the "special" characters in text, it will generally be OK -- reStructuredText is pretty smart. For example, this lone asterisk * is handled just fine, as is the asterisk in this equation: 5*6=30. If you actually want text *surrounded by asterisks* to not be italicised, then you need to indicate that the asterisk is not special. You do this by placing a backslash just before it, like so "\*". Inline markup by itself (surrounded by whitespace) or in the middle of a word won't be recognized - it has to be escaped like in the following sentence:

Possible in *re*\ ``Structured``\ *Text*, though not encouraged.

Inline markup that requires definitions
=======================================

External Hyperlink Targets
--------------------------

reference_ - append ``_`` to the word (``reference_``).

`phase reference`_ - surround text by ````` and then append ``_`` (```phase reference`_``). It's just like reference but if the content contains spaces it must be surrounded by `````.

anonymous__, `anonymous phase reference`__ - just like (phase) reference but the definition will not use the name, but ``__``. Anonymous references definition order must match their appearance.

Hyperlinks can have embedded URIs, like `Python <http://www.python.org/>`_. Such references do not need definition.

Links inside the website
------------------------

Nikola has a `built-in feature <https://getnikola.com/path-handlers.html>`__ do to it, like this: `reST examples <link://filename/pages/test/rest_examples.rst>`__.

Internal Hyperlink Targets
--------------------------

Internal crossreferences, like `internal reference`_.

Indirect Hyperlink Targets
--------------------------

The second hyperlink target (the line beginning with "__") is both an indirect hyperlink target (*indirectly* pointing at the Python website via the "Python_" reference) and an **anonymous hyperlink target**. In the text, a double-underscore suffix is used to indicate an **anonymous hyperlink reference**. In an anonymous hyperlink target, the reference text is not repeated. This is useful for references with long text or throw-away references, but the target should be kept close to the reference to prevent them going out of sync.

Python_ is `my favourite
programming language`__.

Implicit Hyperlink Targets
--------------------------

Section titles, footnotes, and citations automatically generate hyperlink targets (the title text or footnote/citation label is used as the hyperlink name).

Implict references, like `Heading 2`_ are automatically linked.

Explicit Markup
===============

Explicit markup blocks are used for constructs which float (footnotes), have no direct paper-document representation (hyperlink targets, comments), or require specialized processing (directives). They all begin with **two periods and whitespace**, the "explicit markup start".

The numbering of auto-numbered footnotes is determined by the order of the footnotes, not of the references. For auto-numbered footnote references without autonumber labels (``[#]_``), the references and footnotes must be in the same relative order. Similarly for auto-symbol footnotes (``[*]_``).

|RST| - replace reference. Surround text by ``|``. Replace references can also be defined as link, causing both effects to take place.

footnote reference [101]_, citation reference [CIT2020]_ - add text in brackets and append ``_`` (``[101]_``, ``[CIT2020]_``).

.. lines below are definitions, they will not be rendered except for footnote and citation

.. _`internal reference`:

This is an example crossreference target. It is not defined together with other references but instead it points to this paragraph.

.. _reference: link here
.. _phase reference: link here
.. _Python: http://www.python.org/
__ first anonymous reference - link here
__ second anonymous reference - link here
__ Python_
.. |RST| replace:: reStructuredText
.. _RST: http://docutils.sourceforge.net/rst.html
.. [101] note the lack of colon in footnote definition
.. [CIT2020] note the lack of colon in citation definition

Inline markup - HTML
====================

Forbidden. **Do not use HTML tags inside reStructuredText pages**. |RST| exists with its features to avoid manually writing HTML (or other output-specific) markup.

Lists
=====

Implemented lists
-----------------

Note that a blank line is required before the first item and after the last, but is optional between items.

Bullet lists:

- This is item 1
- This is item 2
- Bullets are "-", "*" or "+".
  Continuing text must be aligned
  after the bullet and whitespace.

  - This is a sublist.  The bullet lines up with the left edge of
    the text blocks above.  A sublist is a new list so requires a
    blank line above and below.

Enumerated lists:

1. This is the first item
2. This is the second item
3. Enumerators are arabic numbers,
   single letters, or roman numerals
4. List items should be sequentially
   numbered, but need not start at 1
   (although not all formatters will
   honour the first index).
#. This item is auto-enumerated

Unsupported lists
-----------------

Not recommended to use, not implemented yet and likely will not be needed:

- definition list
- field list
- option list

Block Quotes
============

Block quotes are just:

    Indented paragraphs,

        and they may nest.

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

A transition marker is a horizontal line of 4 or more repeated punctuation characters.

------------

A transition should not begin or end a section or document, nor should two transitions be immediately adjacent.

Directives
==========

Directives are a general-purpose extension mechanism, a way of adding support for new constructs without adding new syntax. For a description of all standard directives, see `reStructuredText Directives <https://docutils.sourceforge.io/docs/ref/rst/directives.html>`_.

Image
-----

Most useful options: ``alt`` and ``target`` (clickable image).

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

Including an External Document Fragment
---------------------------------------

The "include" directive reads a text file. The directive argument is the path to the file to be included, relative to the document containing the directive. For example::

    This first example will be parsed at the document level, and can
    thus contain any construct, including section headers.

    .. include:: inclusion.txt

    Back in the main document.

This can be useful for articles/tutorials which share same/similar set of information.

Parsed Literal Block
--------------------

Unlike an ordinary literal block, the "parsed-literal" directive constructs a literal block where the text is parsed for inline markup. It is equivalent to a line block with different rendering: typically in a typewriter/monospaced typeface, like an ordinary literal block. Parsed literal blocks are useful for adding hyperlinks to code examples.

However, care must be taken with the text, because inline markup is recognized and there is no protection from parsing. Backslash-escapes may be necessary to prevent unintended parsing. And because the markup characters are removed by the parser, care must also be taken with vertical alignment. Parsed "ASCII art" is tricky, and extra whitespace may be necessary.

This can be useful for presenting heavily-formatted text that is not strictly code. A good example are grammar specifications:

.. parsed-literal::

    *function-specifier*:
        virtual
        *explicit-specifier*

    *explicit-specifier*:
        explicit ( *constant-expression* )
        explicit

    *placeholder-type-specifier*:
        *type-constraint*\ (optional) auto
        *type-constraint*\ (optional) decltype ( auto )

Code
----

The "code" directive constructs a literal block. Language and ``number-lines`` options are optional. Currently there is no Pygments-based highlighting. The indent needs to be the same for directive options and directive content.

.. code:: python
    :number-lines:

    def my_function():
        "just a test"
        print 8/2

Custom directives
=================

Details element
---------------

Creates spoiler-like element, using HTML ``<details>`` tag. Support through ``details_element`` plugin.

- Optional option: ``open`` (no arguments), causes the details element to be initially open (``<details open>``).
- Required option: ``summary``, text to always display (``<summary>``)

.. details::
    :summary: summary

    content, which may be arbitrary reST content

    - list item A
    - list item B
    - list item C

Custom code highlight
---------------------

Support through ``rest_highlighter`` plugin.

- Optional option: ``lang``, defaults to CSS class used for C++.
- Paths to code and color spec are mandatory. If paths begin with ``/``, they are relative to the ``conf.py`` file, otherwise they are relative to the file containing the directive.

.. cch::
    :code_path: test_code.cpp
    :color_path: test_code.color

Custom ANSI highlight
---------------------

Support through ``rest_highlighter`` plugin.

- Path to ANSI text is mandatory. If the path begins with ``/``, it is relative to the ``conf.py`` file, otherwise it is relative to the file containing the directive.

.. ansi::
    :ansi_path: test_ansi1.txt

.. ansi::
    :ansi_path: test_ansi2.txt

Admonitions
-----------

There are some predefined admonitions but they do not allow to change the title text, which is a reason big enough to abandom them. Use only these custom admonitions:

.. admonition:: Note
   :class: note

   This is a note.

.. admonition:: Warning
   :class: warning

   This is a warning.

.. admonition:: Error
   :class: error

   This is an error.

.. admonition:: Tip
   :class: tip

   This is a tip.

.. admonition:: Success
   :class: success

   This is a succes sign.

.. admonition:: Definition
   :class: definition

   This is a definition.

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

For example:

    Copyright |copy| 2003, |BogusMegaCorp (TM)| |---|
    all rights reserved.

    .. |copy| unicode:: 0xA9 .. copyright sign
    .. |BogusMegaCorp (TM)| unicode:: BogusMegaCorp U+2122
       .. with trademark sign
    .. |---| unicode:: U+02014 .. em dash
       :trim:

Unsupported
===========

Do not use these:

- literal blocks
- line blocks
- doctest blocks
- ``date``/``time`` - they are run whenever page is regenerated, not when a commit actually changes the page - this creates a ton of false positives

...and anything else not mentioned on this page.
