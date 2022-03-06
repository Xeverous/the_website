.. title: 02 - comments
.. slug: 02_comments
.. description: C++ comments
.. author: Xeverous

C++ supports 2 different ways of writing comments:

- Single-line - they start with ``//`` and span until end of line.
- Multi-line: they start with ``/*`` and span until ``*/``. Both of these can be on the same line, so multi-line comments can also be used as very short comments, mixed with code on the same line.

Multi-line comments are sometimes called C-style comments as this syntax originally appeared in C++ ancestor - the C language. Since 1999 standard C also supports single-line (C++-style) comments.

.. cch::
    :code_path: 02_comments/syntax.cpp
    :color_path: 02_comments/syntax.color

Multi-line comments can be used to disable multiple lines of code at once. Just wrap the code in them and the code will no longer be considered code but a comment. You can also notice that multi-line comments can contain single-line comments - in other words, multi-line comments can "eat" any other text between their start and end tokens.

.. admonition:: definition
    :class: definition

    Multi-line comments can not be nested. Some compilers may emit a warning if they encounter multiple ``/*`` without ``*/`` between.

If you try to nest such comments (e.g. ``/* /* ... */ */``):

- the first ``/*`` will begin multi-line comment
- the second ``/*`` will be already a part of the comment text and be ignored
- the first ``*/`` will end multi-line comment
- the second ``*/`` will likely be a syntax error

Backslash at the end of line
============================

Watch out for accidental ``\`` at the end of a line. It extends it to the next one, even in the case of single-line comments:

.. cch::
    :code_path: 02_comments/backslash1.cpp
    :color_path: 02_comments/backslash.color

It's advised to just write 2 comments instead (or 1 multi-line):

.. cch::
    :code_path: 02_comments/backslash2.cpp
    :color_path: 02_comments/backslash.color

Documentation comments
======================

Some tools may automatically help writing pretty comments like this:

.. cch::
    :code_path: 02_comments/doxygen.cpp
    :color_path: 02_comments/doxygen.color

By convention, multi-line comments beginning with ``/**`` (or single-line comments beginning with ``///``) are comments for code-analyzing tools. Compilers ignore text inside comments, but some tools expect certain syntax inside them - e.g. tags denoted with ``@`` are searched by documentation tools like Doxygen which generate documentation from code. Some IDEs may also display help boxes by relying on these tags.

Purpose of comments
===================

In ordinary code the main purpose of comments is documentation and explaining *why* something is done, not *how*. Very often there are many ways to do certain task. Code will describe *how* to do this task. But *why* this particular way? This should be written in the comment so that when the code is read the decision about particular solution is understood.

Example, bad:

.. cch::
    :code_path: 02_comments/bargain_bad.cpp
    :color_path: 02_comments/bargain.color

Example, good:

.. cch::
    :code_path: 02_comments/bargain_good.cpp
    :color_path: 02_comments/bargain.color

In the example above the comment should not explain math (reducing amount by percents is pretty straightforward) but why there is a special case for bargains exceeding 100% - in such cases the player could abuse the game by reducing price to negative numbers, potentially ending up earning money while buying the item.

In the tutorial this rule will obviously be violated as the goal here is to teach you programming. Just be aware that in professional code comments should not explain code as we should assume the reader is already familiar with the language. It's more important to save what can not be stated in the code so if you think something is significant - write it down. At first it might seem trivial and you will remember it but once you start making bigger projects or work with other people you will realize how unlikely it is that someone will remember all of the obvious things in the program that has multiple thousand lines of code.

Formatting
##########

A battle almost as old as deciding which side toiler paper should go on is code formatting, especially braces (``{}``).

Below I present 2 most common formatting styles found in C and C++ code:

.. cch::
    :code_path: 02_comments/formatting.cpp
    :color_path: 02_comments/formatting.color

A much larger list can be found on https://en.wikipedia.org/wiki/Indentation_style.

For beginners, Allman will usually be better as with it it's easier to reason about indented code. K&R main advantage is more concise code, allowing to fit more on fewer lines. Not every brace in K&R is placed on the same line - function-opening brace is placed on the next. IDEs may also feature automatic code formatting tools.

A different issue is maximum allowed line length. There is no technical limit, but most people break long lines once they become too long - vertical scrolling is fine but hardly anyone likes horizontal scrolling. Sticking to a line length limit lets people open multiple editors side by side. Recommendations vary. In the past it was 80, partially due to technical reasons but now it's not rare to find projects with maximum 120 or 150 characters in line.

If you happen to split a line, it's recommended to align the code (similarly how you can find aligned comments in the tutorial lessons) and place the operator on the next line - if expression like :cch:`2 * 3 + 4 * 5$$$num * num + num * num` is split over ``+``, the ``+`` character should be first on the next line, not last on the previous line (this increases readability).

.. admonition:: tip
    :class: tip

    Pick a style you prefer and use it consistently.

A well-formatted program is easier to understand. This is hilariously explained in `CppCon 2018: James McNellis "The Shape of a Program" <https://www.youtube.com/watch?v=P2lxGnbDkDI>`_.

The presentation mentions some simple refactorings (e.g. extracting :cch:`if` statements to unindent nested code) which will be covered in detail in later lessons. There are many simple code transformations you can apply to reduce code complexity; some IDEs even detect such cases and propose automatic refactorings.
