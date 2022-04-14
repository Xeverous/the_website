.. title: 02 - binary system
.. slug: 02_binary_system
.. description: how binary system works
.. author: Xeverous

.. admonition:: note
    :class: note

    This lesson is optional, but understanding how binary system works will help you in some specific programming tasks.

First of all, you should understand that the binary system **is only a different form of writing**. The math is the same, we only represent numbers in a different way. A good comparison would be another writing system - for example roman numerals.

Roman numerals is a system of writing numbers based on sums. M = 1000, D = 500, C = 100, L = 50, X = 10, I = 1, except in case when a lower-value symbol precedes higher value symbol they are subtracted.

- MMDCCLXXIV means 2774 (1000 + 1000 + 500 + 100 + 100 + 50 + 10 + 10 + (5 - 1))
- MMMCMXCIX means 3999 (1000 + 1000 + 1000 + (1000 - 100) + (100 - 10) + (10 - 1))

The systems we use today are *positional systems* which are based on sums of multiplications and they use specific powers of the *system's base* instead of some fixed values.

- 1234 is 1 * 10^3 + 2 * 10^2 + 3 * 10^1 + 4 * 10^0 which is 1 * 1000 + 2 * 100 + 3 * 10 + 4 * 1
- 0.123 is 0 * 10^0 + 1 * 10^(-1) + 2 * 10^(-2) + 3 * 10^(-3) which is 0 * 1 + 1 * 1/10 + 2 * 1/100 + 3 * 1/1000

The only difference between binary system (base 2) and decimal system (base 10) are the powers:

- 1234 is represented as 10011010010 which is 1 * 2^10 + 0 * 2^9 + 0 * 2^8 + 1 * 2^7 + 1 * 2^6 + 0 * 2^5 + 1 * 2^4 + 0 * 2^3 + 0 * 2^2 + 1 * 2^1 + 0 * 2^0 which is 1024 + 128 + 64 + 16 + 2
- 0.123 is not representable in binary because this fraction's denominator does not consist of multiples of 2. In base 10, we can only represent fractions which denominators are multiplies of 2 and 5, in binary - only of 2. Both systems can not represent 1/3: decimal goes 0.3333... and binary goes 0.01010101...

As numbers grow, digits are replaced (0 with 1, 1 with 2, 2 with 3, ...). When max digit is reached (9 in decimal) the mechanism adds another digit on a higher-rank position and resets the current one (9 + 1 = 10, 69 + 1 = 70). This sometimes happens multiple times in a row (99 + 1 = 100, 999 + 1 = 1000). In binary, it's no different. Because there are only 2 digits, the visual length of numbers grows much faster.

The table below showcases natural numbers written in different systems:

.. The table has been generated from a python script.

.. TODO it would be nice to right-align text in this table

.. list-table::
    :header-rows: 1

    * - binary (base 2)
      - octal (base 8)
      - decimal (base 10)
      - hexadecimal (base 16)
    * - 0
      - 0
      - 0
      - 0
    * - 1
      - 1
      - 1
      - 1
    * - 10
      - 2
      - 2
      - 2
    * - 11
      - 3
      - 3
      - 3
    * - 100
      - 4
      - 4
      - 4
    * - 101
      - 5
      - 5
      - 5
    * - 110
      - 6
      - 6
      - 6
    * - 111
      - 7
      - 7
      - 7
    * - 1000
      - 10
      - 8
      - 8
    * - 1001
      - 11
      - 9
      - 9
    * - 1010
      - 12
      - 10
      - a
    * - 1011
      - 13
      - 11
      - b
    * - 1100
      - 14
      - 12
      - c
    * - 1101
      - 15
      - 13
      - d
    * - 1110
      - 16
      - 14
      - e
    * - 1111
      - 17
      - 15
      - f
    * - 10000
      - 20
      - 16
      - 10
    * - 10001
      - 21
      - 17
      - 11
    * - 10010
      - 22
      - 18
      - 12
    * - 10011
      - 23
      - 19
      - 13
    * - 10100
      - 24
      - 20
      - 14
    * - 10101
      - 25
      - 21
      - 15
    * - 10110
      - 26
      - 22
      - 16
    * - 10111
      - 27
      - 23
      - 17
    * - 11000
      - 30
      - 24
      - 18
    * - 11001
      - 31
      - 25
      - 19
    * - 11010
      - 32
      - 26
      - 1a
    * - 11011
      - 33
      - 27
      - 1b
    * - 11100
      - 34
      - 28
      - 1c
    * - 11101
      - 35
      - 29
      - 1d
    * - 11110
      - 36
      - 30
      - 1e
    * - 11111
      - 37
      - 31
      - 1f
    * - 100000
      - 40
      - 32
      - 20
    * - 100001
      - 41
      - 33
      - 21

Hexadecimal numbers are often written with prefix **0x** or suffix **h** to inform that they are hexadecimal. "10" can be of any base but when written as 0x10 or 10h it's clear it's hexadecimal.

The reasons why computers use base 2 are very pragmatic:

- Constructing electronic devices which operate using only 2 states of direct current has gone enormously easier during transistor revolution in XXth century.
- Binary system is the easiest system of all to form from logic functions.

Logic
#####

Logic is a subfield of mathematics. In computer science, boolean algebra plays a huge role - it is used as the theoretical basis of constructing devices that work in the binary system.

When humans add numbers (using decimal system) they do so by applying a set of rules over consecutive digits\ [1]_. Computers do the same task but in the binary system. The rules are applied on the basis of boolean algebra.

In boolean algebra, there are only 2 possible states: false and true. 0 and 1. No and yes. Negative and positive. ...and whatever else you like to call them.

Boolean algebra by itself is not enough to perform computations, but it's a building block for more complex systems.

In this algebra, there are 3 basic operations: NOT, OR and AND. We can think of them as functions - mechanisms which take certain input to provide certain output.

NOT is the simplest of them. It simply reverses the value:

.. list-table::
    :header-rows: 1

    * - x
      - NOT x
    * - 0
      - 1
    * - 1
      - 0

The other 2 are 2-argument functions:

- OR is true when x **or** y is true
- AND is true when x **and** y is true

.. list-table::
    :header-rows: 1

    * - x
      - y
      - x OR y
      - x AND y
    * - 0
      - 0
      - 0
      - 0
    * - 0
      - 1
      - 1
      - 0
    * - 1
      - 0
      - 1
      - 0
    * - 1
      - 1
      - 1
      - 1

- OR is sometimes referred to as boolean addition or maximum function
- AND is sometimes referred to as boolean multiplication or minimum function

Out of these functions, it's possible to construct more complex ones:

- x NOR y is equivalent to NOT (x OR y)
- x NAND y is equivalent to NOT (x AND y)
- x XOR y (e\ **x**\ clusive OR) is equivalent to:

  - (x OR y) AND NOT (x AND y)
  - (x OR y) AND (NOT x OR NOT y)

- x NXOR y is equivalent to NOT (x XOR y) which is also equivalent to:

  - (x AND y) OR NOT (x OR y)
  - (x AND y) OR (NOT x AND NOT y)

.. list-table::
    :header-rows: 1

    * - x
      - y
      - x NOR y
      - x NAND y
      - x XOR y
      - x NXOR y
    * - 0
      - 0
      - 1
      - 1
      - 0
      - 1
    * - 0
      - 1
      - 0
      - 1
      - 1
      - 0
    * - 1
      - 0
      - 0
      - 1
      - 1
      - 0
    * - 1
      - 1
      - 0
      - 0
      - 0
      - 1

All of these functions are often referred to as `logic gates <https://en.wikipedia.org/wiki/Logic_gate>`_.

Numberphile has made `a video <https://www.youtube.com/watch?v=lNuPy-r1GuQ>`_ explaining how you can build logic gates using dominos. Through junctions and collisions you can imitate elements such as diode and transistor. Later they showcase a 10000 domino circuit that adds 2 4-bit integers.

Below is an example of the 7400 chip which contains 4 NANDs. The two additional pins supply power (+5 V) and connect the ground.

.. image:: https://upload.wikimedia.org/wikipedia/commons/c/c6/TexasInstruments_7400_chip%2C_view_and_element_placement.jpg
    :alt: The 7400 chip

Connecting output of gates to the input of other gates allows to build complex circuits which can perform various computational tasks, including arithmetic in the binary system. Below is a 4-bit *multiplexer* which depending on the value of selectors (S0, S1), forwards one of the inputs (I0, I1, I2, I3) to the output:

.. image:: https://upload.wikimedia.org/wikipedia/commons/9/95/4to1_MUX_using_basic_gates.jpg
    :alt: 4-bit multiplexer

The truth table for this device:

.. list-table::
    :header-rows: 1

    * - S0
      - S1
      - output
    * - 0
      - 0
      - I3
    * - 0
      - 1
      - I1
    * - 1
      - 0
      - I2
    * - 1
      - 1
      - I0

Below is the 74181, a 4-bit ALU (arithmetic logic unit):

.. image:: https://upload.wikimedia.org/wikipedia/commons/c/c0/74181aluschematic.png
    :alt: 74181 4-bit arithmetic logic unit

The device has many inputs:

- 4-bit data A (A0, A1, A2, A3)
- 4-bit data B (B0, B1, B2, B3)
- 4-bit function selector (S0, S1, S2, S3)
- Carry (Cn)
- Mode (M)

And many outputs:

- 4-bit function result (F0, F1, F2, F3)
- A = B bit
- Carry (C(n+4))
- ??? (P)

Selectors decide what the ALU is doing. Since there are 4 selection bits, the device can perform 2^4 = 16 different functions (which means 16 truth tables for inputs A and B), each with specific Mode and Carry. Some of possible operations are:

- addition of 2 4-bit integers (first integer represented in binary system by A inputs, second by B) (if sum does not fit in 4 bits it's signaled through Carry output)
- subtraction of 2 4-bit integers (if result is negative it's signaled through Carry output)
- bitwise logical operations (e.g. F0 = A0 XOR B0, F1 = A1 XOR B1, ...)
- bit shift operations (e.g. F0 = 0, F1 = A0, F2 = A1, F3 = A2)

At this point you should understand how computers work. Modern hardware is made of highly-integrated circuits which can contain billions of transistors.

----

.. [1] If you are confused with the terminology: *numbers* are made of *digits*. There are infinitely many numbers but we use a finite set of digits (0, 1, 2, 3, 4, 5, 6, 7, 8, 9 in decimal system) to represent them.
