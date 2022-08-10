.. title: 04 - types
.. slug: index
.. description: basic types in C++
.. author: Xeverous

.. admonition:: note
    :class: note

    This lesson presents a lot of detailed information, which you do not have to remember - it's given for the sake of knowledge/example if one is really interested. You only need to understand concepts behind various types and their main characteristics.

Computer memory has been changing over time and while storage technologies continue to evolve, the way memory is used from software point of view has settled on a very simple and effective design: a flat addressing model. Every cell contains exactly 1 byte (where for the vast majority of hardware a byte stores 8 bits) of information and has a unique address. There might be a very complex structure in the hardware but as far as software is concerned, it sees memory as one long sequence of cells with growing addresses.

    What about CPU cache? Isn't this some other form of memory?

Not really. Additional mechanisms such as registers and caches are not extra memory - they are a copy of existing memory for faster access. Each time cache is filled with data expected to be used soon, it contains a temporary copy of specific address range of main memory. Program instructions are generally unware of these mechanisms - they simply ask for data under certain address.

Computers read, write and manipulate data in binary. But what does the data represent? How to interpret it? This is what types are for. Since memory by itself has no notion of what data represents, it's all up to the programmer to give it a meaning by specifying a type. A number without a context is just a number. But with specific interpretation, it can mean text (each symbol having unique number), color (numbers stating intensity of RGB components), sound (numbers describing physical attributes of waves) and so on - for this reason files have extensions - a file is nothing more than a sequence of bytes. It's up to the user which program to use to open it and how the program will interpret this sequence.

In C++, every *object* has an associated type. This makes C++ a **statically typed programming language**. The type determines multiple memory-related properties (including size in bytes) and how the binary representation should be interpreted and what operations can be performed on the data. Two objects with different types may be identical in their binary form (the same bit pattern), but their meaning can be completely different.

    What if a language is not statically typed?

Such languages have **dynamic typing**. They do not require specifying types of objects. Objects dynamically adapt (during program execution) by performing hidden conversions between type-mismatched operations. These languages are typically run on virtual machines or by interpreters - they rarely are transformed into real machine code - generally, they wouldn't be as efficient as a statically-typed language so instead they go for the benefits of being interpreted (e.g. no compilation required).

C++ is a language which does not do anything unless explicitly asked to (for performance reasons). You have the full control what happens, when and how. If you want extra behavior such as dynamic typing, there are mechanisms in C++ that can be used for it. Otherwise, you don't pay for what you don't use.

Advantages of static typing:

- Less mistakes: type-mismatched operations result in compiler errors. For interpreted languages, such problems are usually detected only when the program is run and only when the faulty operation is attempted.
- Faster execution: less convertions are performed.
- Lower memory usage: each object is stored on fixed amount of memory. With dynamic typing variables have to be stored multiple times in different formats or to have prepared extra memory.
- Self-documenting code: you know exactly what you work with. No need to write explanatory comments what kind of data is accepted in specific places. Said differently, in statically typed languages you see variable and type names, in dynamically typed languages you see only variable names.
- Better optimization: Compilers generate better machine code knowing exactly how memory is used.

The first point might seem trivial but convertion errors are a common source of bugs in software. By specifying types we give variables specific purpose and prevent mistakes from wrong interpretation. This is known as **type safety**. C++ takes type safety very seriously - as a programming language it has one of the richest type systems.

Types in C++
############

There are 2 kinds of types in C++:

- built-in types - types offered by the language itself, they are denoted with keywords
- user-defined types - types created by the user (here *user* means a user of the language - programmer); these are defined in code using specific keywords (:cch:`struct`, :cch:`class`, :cch:`enum`) and then their name from definition is used

For now, we will stick to built-in types as defining new types requires more knowledge. Sometimes we will use user-defined types from the standard library. All you need to know for now is that user-defined types allow to specify new meanings for binary data which is extremely useful in making abstractions.

    Is :cch:`std::cout` such user-defined type?

No. It is an object. A globally accessible object of user-defined type :cch:`std::ostream`.

Most important built-in types:

- :cch:`void` - represents nothingness. You can not create objects of this type but :cch:`void` can be used in some contexts to express that no data is being used.
- :cch:`bool` - represents a boolean value.
- integer types - capable of storing whole numbers.
- character types - *integral* types which main purpose is storing text.
- floating-point types - capable of storing real numbers with fractional and/or exponential part, with limited accuracy.

.. admonition:: definition
  :class: definition

  **Integral** types are :cch:`bool`, integer, character and (if any) implementation-defined extended integer types.

The type :cch:`bool`
====================

This type represents a mathematical truth value (AKA logical value). It can hold exactly 1 of 2 possible values: :cch:`false` and :cch:`true`.

:cch:`bool` can be thought as a single bit (0 or 1).

:cch:`bool` will be most often used with :cch:`if` and other control flow statements.

Integer types
=============

Most numbers will require multiple memory cells. A single byte consisting of 8 bits can only represent 256 (2^8) distinct values - such small range is too low for most situations. Most code will use 32-bit and 64-bit integer types.

Integers have 2 independent properties:

- length - amount of memory cells they occupy. The more memory they occupy, the wider range of numbers they can represent.
- signedness - if number is signed, its first bit does not contribute to its magnitude but is used as +/- sign instead.

Signed numbers can represent negative values. Unsigned can not, but the extra bit allows twice as many representable magnitudes.

.. list-table::
    :header-rows: 1

    * - length (in bits)
      - unsigned range
      - signed range
    * - 8
      - 0 - 255
      - -128 - 127
    * - 16
      - 0 - 65535
      - -32768 - 32767
    * - 32
      - 0 - 4 294 967 295
      - -2 147 483 648 - 2 147 483 647
    * - 64
      - 0 - 18 446 744 073 709 551 615
      - -9 223 372 036 854 775 808 - 9 223 372 036 854 775 807

..

    Why signed integers have 1 more possible negative value? Shouldn't this be e.g. -127 - 127?

It actually could be that way if hardware used *sign and magnitude* notation to represent negative numbers. Basically, all bits except one would mean the number magnitude (written similarly as humans do, but in base 2 instead of base 10) and the last bit meaning + or - sign. However, there is one huge problem with this notation - it allows 2 representations for zero: +0 and -0. Having 2 different possible representations for the same value is very undesirable - it would significantly complicate electrical circuits to support comparison and other mathematical operations.

Here is a table comparing different interpretations of the same 4-bit pattern:

.. list-table::
    :header-rows: 1

    * - binary
      - unsigned
      - sign and magnitude
      - ones' complement
      - two's complement
    * - 0000
      - 0
      - 0
      - 0
      - 0
    * - 0001
      - 1
      - 1
      - 1
      - 1
    * - 0010
      - 2
      - 2
      - 2
      - 2
    * - 0011
      - 3
      - 3
      - 3
      - 3
    * - 0100
      - 4
      - 4
      - 4
      - 4
    * - 0101
      - 5
      - 5
      - 5
      - 5
    * - 0110
      - 6
      - 6
      - 6
      - 6
    * - 0111
      - 7
      - 7
      - 7
      - 7
    * - 1000
      - 8
      - -0
      - -7
      - -8
    * - 1001
      - 9
      - -1
      - -6
      - -7
    * - 1010
      - 10
      - -2
      - -5
      - -6
    * - 1011
      - 11
      - -3
      - -4
      - -5
    * - 1100
      - 12
      - -4
      - -3
      - -4
    * - 1101
      - 13
      - -5
      - -2
      - -3
    * - 1110
      - 14
      - -6
      - -1
      - -2
    * - 1111
      - 15
      - -7
      - -0
      - -1

.. Generally, ** should be used for emphasis but bolded ' is hardly noticeable so inline code is used instead in the question below.

..

    Why ones\ ``'`` and two\ ``'``\ s complement?

The apostrophe placement is related to english grammar rules and the fact that the first of the terms refers in plural form while the second in singular. See https://english.stackexchange.com/a/145101 and https://english.stackexchange.com/a/520902 for more information.

Computer hardware is using two's complement to represent signed numbers. It has multiple advantages:

- it avoids problems caused by 2 representations for zero
- it has very simple convertion to/from unsigned representation
- multiple math operations have the same implementation for unsigned and two's complement representation, so the same circuit can perform math on numbers in both forms, example:

  - unsigned: addition of 127 (0111 1111) and 128 (1000 0000) is 255 (1111 1111)
  - two's complement: addition of 127 (0111 1111) and -128 (1000 0000) is -1 (1111 1111)

..

    Do I need to remmeber all of this?

No. Bit-level knowledge is suplementary and is not required except in bitwise operations, which are rarely used. I present this knowledge because the fact that numbers in computers have many limitations (especially floating-point types) was very surprising for me.

Integer types - keywords
------------------------

The simplest integer type is :cch:`int`.

- Length can be modified using keywords :cch:`short` and :cch:`long`, where :cch:`long` can appear twice.
- Signedness can be modified using keywords :cch:`signed` and :cch:`unsigned`. By default, numbers are signed.

Unnecessary keywords can be skipped so:

- :cch:`unsigned short int` can be shortened to :cch:`unsigned short`
- :cch:`signed short int` can be shortened to :cch:`short`
- :cch:`signed long long int` can be shortened to :cch:`long long`
- :cch:`int` can also be written as :cch:`signed`

..

    Is :cch:`short long` a valid type?

No.

    Is :cch:`int long unsigned long` a valid type?

Yes, but to put it simply, other people will not be happy if you write types this way. The convention is signedness followed by length. Skipping unnecessary keywords is fine.

    What lengths do they actually have?

Exact lengths depend on the hardware for which the code is compiled but it is guuaranteed that larger types have equal or wider range of representatable values, e.g. :cch:`long long` can store everything that :cch:`long` can.

Most commonly implemented lengths on x86 (32-bit PC), x86-64 (64-bit PC) and 64-bit ARM (common architecture for mobile devices):

- :cch:`short` is 16-bit
- :cch:`int` is 32-bit
- :cch:`long` is 32-bit or 64-bit
- :cch:`long long` is 64-bit (if supported by the hardware)

In any case, if you need integer types of certain length - either because you need to ensure that specific range is representable or because you use specific bit-related instructions, you should use `fixed-width integer type aliases found in the standard library <https://en.cppreference.com/w/cpp/header/cstdint>`_. More on this later. For now, just remember you can only vaguely rely on integer lengths.

Additional (non-standard) types may be offered by the compiler (e.g. :cch:`__int128` in GCC).

    What integer type should I use when writing code? Is there any guideline?

By default, use :cch:`int`. It is the default integer type in most projects and its size/range tradeoff is very good for 99% of applications. Don't use :cch:`unsigned` just because a number can not be negative. Unsigned numbers undego different optimizations and should only be used for bit-level operations.

Character types
###############

Generally, text is stored as a sequence of numbers where each number has an associated meaning. In simple writing systems such as latin it's 1 number for 1 letter, in others it gets more complex (e.g. 1 number for "base shape" and 1 number for diacritics). *Unicode* is the most widespread text system. It aims to support every writing system possible (including historical ones) but due to it's complexity it will be taught in a later chapter. For now, just remember that Unicode has multipe ways (*encodings*) of representing the same text.

Character types in C++:

- exactly one byte: :cch:`char`, :cch:`unsigned char`, :cch:`signed char`
- :cch:`wchar_t` - size depends on the target platform preferred wide character encoding (16-bit for Windows which uses UTF-16LE encoding, 32-bit for others which use UTF-32)
- fixed-width (always unsigned):

  - :cch:`char8_t` (since C++20)
  - :cch:`char16_t`
  - :cch:`char32_t`

:cch:`char` has the same implementation as one of its variants with specified signedness, but is a distinct type at the language level. Thus, while :cch:`int` is the same as :cch:`signed int`, :cch:`char` is a distinct character type from :cch:`signed char` and :cch:`unsigned char`.

Floating-point types
####################

.. TOLATEX

Types used to represent real numbers are named floating-point because they allow to shift the point - they are stored using exponential (AKA scientific) notation. For example: ``-123 * 10^(-456)``.

Floating-point types consist of two parts - the **mantissa** ``m`` (AKA **significant**) and **exponent** ``p``. In computers the base is 2, so real numbers are stored as ``m * 2^p``, not ``m * 10^p``.

For example:

- ``416`` can be stored as ``13 * 2^5``, ``26 * 2^4``, ``52 * 2^3``, ``104 * 2^2``, ``208 * 2^1``
- ``0.05078125`` can be stored as ``13 * 2^(-8)``, ``26 * 2^(-9)``, ``52 * 2^(-10)``, ...

Floating-point representations are standarized and practically all hardware adheres to `IEEE-754 <https://en.wikipedia.org/wiki/IEEE_754>`_. This allows consistent results regardless of used operating system or programming language.

On a hardware that satisfies IEEE-754 standard:

- 32 bit floating-point type uses:

  - 1 bit for sign
  - 23 bits for *mantissa*
  - 8 bits for *exponent*

- 64 bit floating-point type uses:

  - 1 bit for sign
  - 52 bits for *mantissa*
  - 11 bits for *exponent*

The bit sign affects mantissa. Exponent does not need a bit sign because its base has an offset: for 8-bit exponent, its range is not 0 - 255 but -128 - 127. In other words, exponent behaves like unsigned integer but its value is always interpreted as lower by 128.

    Why signed integers use two's complement but floating-point mix sign and magnitude notation with offset unsigned?

In short, such implementation is the simplest one. Be aware that sign for exponent does not make the number negative but reciprocal instead: ``m * 2^(-p) = 1/m * 2^p``. ``2^5`` is ``32`` but ``2^(-5)`` is ``1/32``, not ``-32``. Additionally, floating-point math has significantly different usage. All these factors cause different tradeoffs regarding optimal hardware implementation.

    Due to separate sign bit, do floating-point types allow positive and negative zero?

Yes. 0 raised to any power will be 0, so apart from the bit sign, the exponent can also vary.

C++ offers 3 floating-point types:

- :cch:`float` (single precision) - IEEE-754 32-bit floating-point type
- :cch:`double` (double precision) - IEEE-754 64-bit floating-point type
- :cch:`long double` (extended precision) - not necessarily any IEEE standard, on x86 and x86-64 architectures uses special 80-bit registers

Additional (non-standard) types may be offered by the compiler (e.g. :cch:`__float128` in GCC).

Special values
==============

Floating-point types support special values. These are mostly intended for mathematical functions which can not output a valid answer (e.g. because the argument is out of domain).

- infinity - all exponent bits set to ``1`` and all mantissa bits set to ``0``. Instead of treating this as "zero to a very huge power" it is treated as infinitely large number. The existence of infinity helps to detect possible calculation errors. Infinity can also be negative.
- NaN (not a number) - all exponent bits set to ``1`` and any non-zero mantissa. The purpose of NaNs is to indicate logic errors - for example, a logarithm can not take negative number as an argument, hence ``log(-1) = NaN``.

.. cch::
    :code_path: special_fp_values.cpp
    :color_path: special_fp_values.color

Operations on special values will generally propagate them further, e.g. infinity +/- any proper value will be infinity, NaN +/- any proper value will be NaN. This is desirable, because if at any point there is a logical mistake it's much better to get clearly meaningless result than to be fooled by something looking valid that came from wrongly written code.

Floating-point limitations
==========================

Floating-point limits are not so straightforward as for integers due to their complex notation.

Both mantissa and exponent have their own limits, so there is both maximum/minimum magnitude and maximum/minimum power it can be raised to. In other words, we can speak about:

- largest representable positive and negative value (+/- sign, max m, max p)
- smallest representable positive and negative value, different than 0 (+/- sign, min m, min p)
- granularity: what is the smallest possible difference between 2 consecutive numbers; **granularity is not constant**

**Floating-points store real numbers with limited accurary.** Just like in decimal system ``1/3`` can be approximated as ``0.333`` or ``333 * 10^(-3)``, the same problem exists in floating-point notation - the only difference is that base 2 is used instead of base 10 for the exponent. **There are infinitely many values which can not be precisely represented** - instead, the closest approximations are used.

Shortly speaking, granurality increases (more values can be represented in the given subrange) the closer they are to 0. The highest precision is in range ``-0.1`` to ``0.1``. Analogy: ``100`` and ``101`` can be exactly represented. But in case of ``1000000001``, it might be approximated as ``1 * 10^9`` when mantisa does not have enough bits to support ``1000000001 * 10^1``. As numbers grow, more focus is placed into the exponent which causes magnitude to be more rounded towards specific power. Past some point, all odd values are approximated to closest even value.

    If floating-point math has limited accuracy, how do calculators work then? How are various fractional values safely computed?

In places such as finance where accuracy is paramount integers are used for calculations. Monetary amounts like ``1.5`` (in any currency that has denomination of 100) are stored as ``150``. The same method is commonly found in games - various fractional statistics are multiplied by 100 or 1000 so that all math can happen on whole numbers. Math on integer types is also faster.

Calculators with unlimited precision don't use floating-point arithmetic. They store integers as arrays which can have arbitrarily large size (each cell does not necessarily represent each digit - it's more complicated). They store fractions as 2 integers (numerator and denominator), they don't immediately evaluate every function, they don't simplify formula if it would lose accuracy and so on. Basically, they store information using complex data structures and perform operations using methods very similar to humans. This allows to support arbitrarily complex expressions without losing precision, but the logic that handles them is enormously complicated.

    I'm concerned with limited accuracy. How safe is using floating-point representation?

Very safe. In vast majority of applications:

- Error margin is multiple orders of magnitude higher than floating-point inaccuracy (e.g. physical data was measured with 0.01% error, computations had 0.000001% error).
- Accuracy isn't actually important - especially in computer graphics, projects are much more concerned about performance than perfectly positioned pixels (and since computer screens have only few thousand pixels in row/column, their accuracy is somewhere between 1/1000 and 1/10000 - still much bigger error than floating-point).
- Accurate values would be insignificant - in audio processing applications, very small values would represent a signal too quiet to be in the human hearing range.

As a rule of thumb:

- 32-bit (single precision) floating-point has accuracy of 7 decimal places
- 64-bit (double precision) floating-point has accuracy of 15 decimal places

More to come
============

If you feel a bit overwhelmed by the complexity of floating-point types, don't worry - further lessons will feature example code showcasing many of their peculiarities.

.. TODO Exercise? List some types names and ask whether they are the same?
