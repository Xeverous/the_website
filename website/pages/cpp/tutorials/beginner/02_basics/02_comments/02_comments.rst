.. title: 02 - comments
.. slug: index
.. description: C++ comments
.. author: Xeverous

C++ supports 2 different ways of writing comments:

- Single-line - they start with ``//`` and span until end of line.
- Multi-line: they start with ``/*`` and span until ``*/``. Both of these can be on the same line, so multi-line comments can also be used as very short comments, mixed with code on the same line.

The C++ ancestor, C, originally supported only multi-line comments. In 1999 standard (referred to as C99) it adopted single-line comments from C++. Thus:

- ``/*`` ``*/`` are sometimes referred to as "C-style comments"
- ``//`` are sometimes referred to as "C++-style commnents"

.. cch::
    :code_path: syntax.cpp
    :color_path: syntax.color

Multi-line comments can be used to disable multiple lines of code at once. Just wrap the code in them and the code will no longer be considered code but a comment. You can also notice that multi-line comments can contain single-line comments - in other words, multi-line comments can "eat" any other text between their start and end tokens.

.. admonition:: definition
    :class: definition

    Multi-line comments can not be nested. Some compilers may emit a warning if they encounter multiple ``/*`` without ``*/`` between.

If you try to nest such comments (e.g. :cch:`/* /* ... */ */$$$12com_multi 2problem`):

- the first ``/*`` will begin multi-line comment
- the second ``/*`` will be already a part of the comment text and be ignored
- the first ``*/`` will end multi-line comment
- the second ``*/`` will likely be a syntax error

Backslash at the end of line
############################

Watch out for accidental ``\`` at the end of a line. It extends it to the next one, even in the case of single-line comments:

.. cch::
    :code_path: backslash1.cpp
    :color_path: backslash.color

It's advised to just write 2 comments instead (or 1 multi-line):

.. cch::
    :code_path: backslash2.cpp
    :color_path: backslash.color

Documentation comments
######################

Some tools may automatically help writing pretty comments like this:

.. cch::
    :code_path: doxygen.cpp
    :color_path: doxygen.color

By convention, multi-line comments beginning with ``/**`` and single-line comments beginning with ``///`` are comments for code-analyzing tools. Compilers ignore text inside comments, but some tools expect certain syntax inside them - e.g. tags denoted with ``@`` are searched by documentation tools like `Doxygen <https://www.doxygen.nl/index.html>`_ which generate documentation from code. Some IDEs may also display help boxes by relying on these tags.

The purpose of comments
#######################

In ordinary code the main purpose of comments is documentation and explaining **why** something is done, not **how**. Very often there are many ways to do certain task. The code describes *how* to do this task. But *why* this particular way? This should be written in the comment.

Example, bad:

.. cch::
    :code_path: bargain_bad.cpp
    :color_path: bargain.color

Example, good:

.. cch::
    :code_path: bargain_good.cpp
    :color_path: bargain.color

In the example above the comment should not explain math (reducing amount by percents is pretty straightforward) but why there is a special case for bargains exceeding 100% - in such cases the player could abuse the game by reducing price to negative numbers, potentially ending up earning money while buying the item.

In professional code comments should not explain code as we should assume the reader is already familiar with the language. It's more important to document *why* a specific block of code exists and *why* a particular solution was choosen. Once you start making bigger projects or work with other people you will realize how unlikely it is that someone will remember all of "the obvious things" in the program that has multiple thousand lines of code.

.. admonition:: tip
  :class: tip

  When writing comments, document *why*, not *how*.

In the tutorial this rule will obviously be violated as the goal here is to teach you programming. Very likely you will also make some notes with explanatory comments. Just be aware that in the actual job the purpose of comments is much different.

Formatting
##########

A battle almost as old as deciding which side toiler paper should go on is code formatting, especially braces (``{}``).

Below I present 2 most common formatting styles found in C and any other language based on C's grammar (such as C++, Java, JavaScript, C#):

.. cch::
    :code_path: formatting.cpp
    :color_path: formatting.color

A much larger list can be found on https://en.wikipedia.org/wiki/Indentation_style.

For beginners, Allman will usually be better as with it it's easier to reason about indented code. K&R main advantage is more concise code, allowing to fit more on fewer lines. Not every brace in K&R is placed on the same line - function-opening brace is placed on the next. IDEs may also feature automatic code formatting tools.

A different issue is maximum allowed line length. There is no technical limit, but most people break long lines once they become too long - vertical scrolling is fine but hardly anyone likes horizontal scrolling. Sticking to a line length limit lets people open multiple editors side by side. Recommendations vary. In the past it was 80, partially due to technical reasons but now it's not rare to find projects with maximum 120 or 150 characters in line.

If you happen to split a line, it's recommended to align the code (similarly how you can find aligned comments in the tutorial lessons) and place the operator on the next line - if expression like :cch:`2 * 3 + 4 * 5$$$num * num + num * num` is split over ``+``, the ``+`` character should be first on the next line, not last on the previous line (this increases readability).

.. admonition:: tip
  :class: tip

  Pick a style you prefer and use it consistently.

A well-formatted program is easier to understand. This is hilariously explained in `CppCon 2018: James McNellis "The Shape of a Program" <https://www.youtube.com/watch?v=P2lxGnbDkDI>`_.

The presentation mentions some simple refactorings (e.g. extracting :cch:`if` statements to unindent nested code) which will be covered in detail in later lessons. There are many simple code transformations you can apply to reduce code complexity; some IDEs even detect such cases and propose automatic refactorings.
