.. title: 07 - literals
.. slug: 07_literals
.. description: C++ literals
.. author: Xeverous

When you initialize or assign an object, data you write in the code (e.g. numbers) is generally stored in some read-only memory block inside the executable.

This data also has a type and there are ways to specify it.

.. admonition:: definition
    :class: definition

    Literals are the tokens of a C++ program that represent constant values embedded in the source code.

Integer literals
################

By default, integer literals are of type :cch:`int`. The type can be changed by applying specific suffix:

.. cch::
    :code_path: 07_literals/integers_suffix.cpp
    :color_path: 07_literals/integers_suffix.color

- The suffix is not case-sensitive but for :cch:`long long`, it must be either ``ll`` or ``LL``. Mixed (``lL`` or ``Ll``) are not valid. Lowercase is recommended.
- There is no suffix for :cch:`short`.

The size type is one of integer types which the target platform uses for storing sizes, indexes etc. Its unsigned variant has an alias name :cch:`std::size_t` and usually it is :cch:`unsigned long long`.

Integers may be written using multiple numeric systems:

.. cch::
    :code_path: 07_literals/integers_base.cpp
    :color_path: 07_literals/integers_base.color

All of the above represent the same value.

Since C++14 numbers may use single quotes to separate digit groups. There are no requirements on grouping, all quotes are simply ignored.

.. cch::
    :code_path: 07_literals/integers_quotes.cpp
    :color_path: 07_literals/integers_quotes.color

..

    What happens if I try to assign/initialize a variable with a literal of a different type?

The value will be converted. If the destination type can not represent the data, some of it might be lost (narrowing conversion). Convertions will be explained in-depth in a later lesson.

Character and string literals
#############################

Characters are stored as numbers. Depending on the encoding, the value in memory can be interpreted as different text.

Character literals use prefixes. They are case-sensitive.

It's possible to write character value directly (in hexadecimal system) by using ``\U`` character.

.. cch::
    :code_path: 07_literals/characters.cpp
    :color_path: 07_literals/characters.color

Don't worry if you don't get UTF information right now, it will be useful later once you learn more about Unicode.

In actual programs, it's really rare to have a need to write characters directly in the code - programs offering translations usually load language-specific text from files.

String literals like :cch:`"abc"` follow identical rules, they can have identical prefixes. Doubly quoted text is simply an array of multiple objects of the same character type.

Encoding used by :cch:`std::cout` is implementation-defined, but every known implementation uses UTF-8. The default encoding for source code files in most situations is also UTF-8, so you shouldn't have problems storing and outputting Unicode text in your programs. If you do, it's usually a matter of project's compiler settings.

:cch:`std::cout` will not accept every possible character type. For :cch:`wchar_t` (and its arrays) you will need to use :cch:`std::wcout`.

String literal concatenation
============================

If multiple string literals are next to each other, only with whitespace between, they behave as if one long string literal. This allows splitting and formatting large blocks of text embedded in code without introducing unwanted line breaks.

.. cch::
    :code_path: 07_literals/concatenation.cpp
    :color_path: 07_literals/concatenation.color

Each quoted string can have own prefix. If one prefix is present, the concatenated string will have the type specified by prefix. If multiple prefixes are present, they all must be the same.

https://en.wikipedia.org/wiki/Lorem_ipsum

Escape sequences
================

Some characters can not be represented easily in text - you have already seen this with line breaks. How about other conflicts? What if we want to output ``'`` or ``"``?

Escape sequences allow to represent troublesome characters in source code by specifying their numeric value or special predefined sequence.

.. list-table::
    :header-rows: 1

    * - sequence
      - description
      - representation
    * - ``\'``
      - single quote
      - byte 0x27
    * - ``\"``
      - double quote
      - byte 0x22
    * - ``\?``
      - question mark
      - byte 0x3f
    * - ``\\``
      - backslash
      - byte 0x5c
    * - ``\a``
      - audible bell
      - byte 0x07
    * - ``\b``
      - backspace
      - byte 0x08
    * - ``\f``
      - form feed (new page)
      - byte 0x0c
    * - ``\n``
      - line feed (new line)
      - byte 0x0a
    * - ``\r``
      - carriage return
      - byte 0x0d
    * - ``\t``
      - horizontal tab
      - byte 0x09
    * - ``\v``
      - vertical tab
      - byte 0x0b
    * - ``\nnn``
      - arbitrary octal value
      - byte *nnn*
    * - ``\Xnn``
      - arbitrary hexadecimal value
      - byte *nn*
    * - ``\c``
      - implementation-defined
      - implementation-defined
    * - ``\unnnn``
      - arbitrary Unicode value; may result in several code units
      - code point U+\ *nnnn*
    * - ``\Unnnnnnnn``
      - arbitrary Unicode value; may result in several code units
      - code point U+\ *nnnnnnnn*

A very common sequence is ``\0`` (represented as byte 0x00) which is the *null character*, used to denote end of data in various contexts.

``\?`` is not necessary, you can write ``?`` directly too but it's kept for backwards compatibility. In the past (before C++17) there was a very weird feature called `trigraphs <https://en.cppreference.com/w/cpp/language/operator_alternative>`_ which allowed 3-character special sequences, parsed even before comments. This feature could accidentally be used by unescaped ``?``.

Because Unicode is ASCII-compatible and ASCII is backwards compatible with very old telegraph systems, you can see some historical control characters:

- ``\a`` caused the machine to output specific sound - see https://en.wikipedia.org/wiki/Bell_character for its history
- ``\f`` - https://en.wikipedia.org/wiki/Page_break#Form_feed
- ``\r`` was used to cause the machine to reset position to the beginning of a line. The ``\r\n`` sequence was very common and in fact, Windows OS uses this sequence up to today - enter key in Windows-based programs outputs this 2-character sequence while every other system outputs only ``\n``. In many editors you can find the setting how line endings should be written: LF (Unix) or CRLF (Windows). As ``\r`` has lost its meaning in the era of screens (not telegrams), programs which display text simply ignore this character. For more history - see https://en.wikipedia.org/wiki/Carriage_return.
- ``\t``, ``\v`` - historically they meant advancement to the next multiple of 8 characters horizontally and 6 lines vertically. ``\v`` is not used anymore but ``\t`` is still widely used to indent code. Editors often allow to change tab size (usually 2/4/8) and convert indentation to/from spaces.

Backspace (``\b``) is used by keyboards to indicate pressed backspace key. If you use this character in a program, its meaning can be different depending what other program will use this data:

- If ``\b`` is written to a text file, it's up to the file reading/displaying program what will be done with it. Most will simply ignore this character.
- If ``\b`` is written to an interactive shell (such as the one in which you can run your compiled programs) the shell will usually discard/overwrite previously output character, just like it was a telegraph machine. A similar behavior can be observed with ``\r`` which will discard/overwrite entire line.

Raw string literals
===================

An alternative to escape sequences are raw strings, in which special characters loose their meaning and everything between delimeters is treated as it is.

The syntax is:

.. parsed-literal::

    *prefix*\ (optional) R"\ *delimiter*\ (\ *raw_characters*\ )\ *delimiter*"

Example:

.. cch::
    :code_path: 07_literals/raw_strings.cpp
    :color_path: 07_literals/raw_strings.color

Raw string literals may span multiple code lines (without concatenation) and they will contain all characters between delimeters, including whitespace such as line breaks.

Raw string literals can be concatenated with other string literals.

Floating-point literals
#######################

By default, floating-point literals are of type :cch:`double`.

- With suffix ``f`` or ``F``, they are :cch:`float`.
- With suffix ``l`` or ``L``, they are :cch:`long double`.

Floating point literals support various formats, including expotential notation and hexadecimal fractions. When using dot (``.``) one of digit sequences is optional.

Examples:

.. cch::
    :code_path: 07_literals/floating_point.cpp
    :color_path: 07_literals/floating_point.color

Other literals
##############

It's worth noting that not all literals have to be made of characters or digits - some literals are keywords. You already know 2 of them: :cch:`false` and :cch:`true` are literals of type :cch:`bool`.

Later you will be learn about one more keyword literal - :cch:`nullptr`.

Automatic type
##############

A simple but very useful feature is the type placeholder :cch:`auto`. It will deduce the type based on the expression used in intialization:

.. TOCOLOR

.. code::

    auto b = true; // bool
    auto i = 1;    // int
    auto l = 1l;   // long
    auto f = 1.0f; // float
    auto x; // error: can't deduce without initializer

.. admonition:: note
    :class: note

    If :cch:`auto` is used, the value must be initialized.

Exercise
########

Try to output the text ``"\n??='\\`` using both escape sequences and raw strings.
