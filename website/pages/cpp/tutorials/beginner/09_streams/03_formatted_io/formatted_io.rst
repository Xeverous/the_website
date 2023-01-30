.. title: 03 - formatted I/O
.. slug: index
.. description: formatted I/O with C++ streams
.. author: Xeverous

All streams in C++ can do formatted or unformatted I/O.

- Unformatted I/O always behaves in the same way.
- Formatted I/O means that resulting data is dependent on stream's state (which also includes currently imbued *locale*).
- operators ``<<`` and ``>>`` are intended for formatted I/O.
- Unformatted I/O and more formatted I/O is available through stream's *member functions*.

Locale is a pretty complex feature intended for localization which can affect formatted I/O and other specific text operations. Due to the size and uniqueness of the feature, it's outside the scope of the tutorial and instead is explained in a separate article TOWRITE. Custom locales are rarely used and the default "C" locale is universal to the point of being able to completely ignore this topic for now.

Everything below is more of a reference than actual lesson - don't try to memorize it. You will do so naturally when there will be a frequent need for such operations. Otherwise just come back here when an occasional need appears.

Formatting states
#################

Each setting is represented by a specific bit in stream's flags. They can be changed using *member functions* and manipulators.

.. cch::
    :code_path: setting_states.cpp
    :color_path: setting_states.color

Because some settings (e.g. base of the output - 8/10/16) are represented by separate bits, you need to set new one and unset previous one:

.. cch::
    :code_path: unsetting_states.cpp
    :color_path: unsetting_states.color

A safer shortcut for this operation is to use a different overload of :cch:`setf$$$func`, one that takes an additional argument which specifies a group of bits to be cleared (called mask):

.. cch::
    :code_path: setting_states_mask.cpp
    :color_path: setting_states_mask.color

Manipulators (which are passed with ``<<``) will automatically disable other bits when necessary.

Manipulators
############

Stream manipulators are functions which are either called (to create an object of specific but *unspecified* type) or passed directly (without calling) to stream insertion/extraction operators (which will call them internally). In any case, operator overloads are defined to support the way in which specific manipulator is intended to be used.

:cch:`bool`
===========

Enable or disable printing words for boolean values (default: numeric).

.. cch::
    :code_path: boolalpha.cpp
    :color_path: boolalpha.color

.. code::

    true false
    1 0

These manipulators also affect input - after :cch:`>> std::boolalpha$$$2oo namespace::func` the stream will expect string representation of boolean values.

Positive numbers
================

Enable or disable printing ``+`` for positive numbers (negative numbers are always printed with ``-``). Affects both integer and floating-point types.

.. cch::
    :code_path: showpos.cpp
    :color_path: showpos.color

.. code::

    -1 +1
    -1 1

.. admonition:: note
  :class: note

  Unlike integer types, floating-point types support multiple forms of representing 0 (the sign bit is independent). This causes floating-point types to have "positive zero" and "negative zero".

These manipulators have no effect on input.

Numeric system and prefix
=========================

- Enable or disable printing base prefix (default: no prefix).
- Specify which base should be used (default: decimal).

These manipulators apply only to integer types.

.. cch::
    :code_path: base.cpp
    :color_path: base.color

.. code::

    in octal       (base  8): 052
    in decimal     (base 10): 42
    in hexadecimal (base 16): 0x2a

    in octal       (base  8): 52
    in decimal     (base 10): 42
    in hexadecimal (base 16): 2a

Strangely, there is no :cch:`std::bin$$$namespace::func` that would print numbers in binary. As a workaround, :cch:`<< std::bitset<N>(val)$$$2oo namespace::type<param_tmpl>(var_local)` can be used.

Prefix manipulators also affect input but only `monetary input <https://en.cppreference.com/w/cpp/io/manip/get_money>`_ which I guess no one uses.

Base manipulators affect both ouput and input. Because each of these 3 manipulators is stored on a separate bit in the stream state flags, there is a possibility that no bit will be set. In such case:

- output is decimal
- input is prefix dependent (no prefix means decimal)

All base state bits can be cleared in 2 ways:

- :cch:`>> std::setbase(0)$$$2oo namespace::func(num)` or :cch:`<< std::setbase(0)$$$2oo namespace::func(num)`
- :cch:`stream.setf(std::ios_base::fmtflags(0), std::ios_base::basefield)$$$var_local.func(namespace::type::type(num), namespace::type::var_global)`

Example:

.. cch::
    :code_path: no_base_bits.cpp
    :color_path: no_base_bits.color

..

    What if multiple bits are set?

No idea, nothing about in on cppreference so I guess the behavior is *unspecified*.

Casing
======

Use uppercase or lowercase letters for numerical output (default: lowercase).

.. cch::
    :code_path: num_case.cpp
    :color_path: num_case.color

.. code::

    0XDEADBEEF 1.23457E+08
    0xdeadbeef 1.23457e+08

You can also observe that default format for floating-point types rounds numbers when using scientific notation.

These manipulators are only for numeric types and do not affect printing text in any way. They have no effect on input.

Point
=====

Enable or disable printing point and decimal fraction digits when not necessary (default: off).

.. cch::
    :code_path: showpoint.cpp
    :color_path: showpoint.color

.. code::

    1.00000 12.3400
    1 12.34

This setting is locale-dependent - locales may specify different character than ``.``.

These manipulators have no effect on input.

Floating-point formats
======================

Specify which format should be used.

.. cch::
    :code_path: fp_format.cpp
    :color_path: fp_format.color

.. code::

    0.001 in fixed:      0.001000
    0.001 in scientific: 1.000000e-03
    0.001 in hexfloat:   0x1.0624dd2f1a9fcp-10
    0.001 in default:    0.001

    1000 in fixed:      1000.000000
    1000 in scientific: 1.000000e+03
    1000 in hexfloat:   0x1.f4p+9
    1000 in default:    1000

These manipulators have no effect on input: parsing of floating-point numbers is unaffected.

Whitespace
==========

Enable or disable skipping whitespace before *formatted input* operations. By default, whitespace is skipped.

.. The example below might seem to be a good candidate to use std::quoted, but std::quoted has only const CharT*, string and string_view overloads.
.. I do not want to write std::quoted(&c, 1).

.. cch::
    :code_path: skipws.cpp
    :color_path: skipws.color

.. code::

    [a], [b], [c], [d],
    [a], [ ], [b], [ ], [c], [ ], [d],

These manipulators have no effect on output.

Whitespace can also be skipped explicitly by doing :cch:`>> std::ws$$$2oo namespace::func`. This operation will consume any consecutive whitespace in the input stream.

Other
=====

There are 2 more manipulators:

- :cch:`std::unitbuf`, :cch:`std::nounitbuf` - disable or enable output buffering (buffering is disabled for :cch:`std::cerr` and :cch:`std::wcerr`); no effect on input
- :cch:`std::left`, :cch:`std::right`, :cch:`std::internal` - showcased further down as these manipulators have effect only in combination with width and fill manipulators

Additional manipulators
#######################

These manipulators are defined in :cch:`<iomanip>`.

Adjustment
==========

Width:

- **Unlike other manipulators**, :cch:`std::setw` (set width) is temporary: it only affects next *formatted I/O* operation. Thus, it's typically used inside loops.
- For *formatted output* operations, it specifies the minimum amount of characters that should be printed. Additional characters are repetitions of the fill character.
- For *formatted input* operations, see next example.
- By default width is zero, which means no additional characters are printed.

Fill:

- Specifies the fill character. Default is space.

Adjustment:

- Specify positioning of fill characters.
- Default adjustment is right, but any adjustment has effect only if width forces to print fill characters. Internal adjustment will separate all kinds of prefixes (``0x`` for hexadecimal, ``-`` for negative numbers and currency symbols if monetary output is used).

.. TODO setw with input operations (for std::string fills N characters, for C arrays fills N-1 + null-terminator)

.. cch::
    :code_path: adjustment.cpp
    :color_path: adjustment.color

.. code::

    1*******
    10******
    100*****
    1000****
    10000***
    100000**
    1000000*
    10000000
    100000000

    .......1
    ......10
    .....100
    ....1000
    ...10000
    ..100000
    .1000000
    10000000
    100000000

    0x_____1
    0x_____a
    0x____64
    0x___3e8
    0x__2710
    0x_186a0
    0x_f4240
    0x989680
    0x5f5e100

Precision
=========

Specify minimum amount of digits that should be printed. This affects only floating-point output.

.. cch::
    :code_path: precision.cpp
    :color_path: precision.color

As a rough guideline:

- :cch:`float` has 6 digits of accuracy
- :cch:`double` has 15
- :cch:`long double` is implementation-defined:

  - 18 in case of Intel's 80-bit floating-point type
  - 33 in case of true IEEE quadruple floating-point type

Other
=====

https://en.cppreference.com/w/cpp/header/iomanip lists a few more but they are very specific and have lots of tiny details. They are hardly ever used.

Exercise
########

.. cch::
    :code_path: exercise.cpp
    :color_path: exercise.color

What does the following program print?

.. details::
  :summary: answer

  .. code::

    +0 +0
    +0 -0

  And why?

  .. details::
    :summary: answer

    Integers have only one representation of 0 and it's regarded as positive (in true mathematical sense 0 is neither positive nor negative). Negating integer 0 does nothing to the underlying bit pattern. Unlike integer types (which use two's complement), floating-point types have a separate bit for sign and thus allow multiple representations for 0, thus they have both "positive zero" and "negative zero".
