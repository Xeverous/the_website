.. title: reStructuredText test
.. slug: rest_test
.. date: 2020-05-20 13:08:52 UTC+02:00
.. tags:
.. category:
.. description: reStructuredText test page
.. type: text
.. author: Xeverous

The following page presents reStructuredText examples and how they look on the site. Compare the source of this page with how it looks on the site (after the build) to learn how everything is rendered.

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

TODO: search for a directive so that there is control of generated HTML class for CSS purposes.

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

The |biohazard| symbol must be used on containers used to dispose of medical waste.

.. |biohazard| image:: https://docutils.sourceforge.io/docs/user/rst/images/biohazard.png

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
