.. title: 08 - operators
.. slug: 08_operators
.. description: basic operators C++
.. author: Xeverous

Basic arithmetic operators in C++ are written using symbols like ``+``, ``-``, ``*`` etc. An **operator** can be thought as a *function* (in mathematical sense) - it has certain input and produces certain output. An operator does not mean a symbol - some operators consist of multiple characters and some are even keywords. *Operator* is an abstract term.

The number of inputs (*operands*) an operator takes is **arity**. C++ features operators with many arities:

- nullary - 0
- unary - 1
- binary - 2
- ternary - 3
- n-ary - n

..

    What's the point of a nullary operator? How can it produce something meaningful with no input?

Well, don't really be concerned with it for now. As you learn more about functions (operators are a specific subset of functions) you will realize how vastly different they can be and that functions taking 0 arguments are still useful. A short example for now can be a function returning current date/time - it doesn't require any input but always provides meaningful output.

Some operators exist with multiple arities. For example:

- unary minus: :cch:`x = -x` (negates number)
- binary minus :cch:`z = x - y` (performs subtraction)

Many operators can be chained to form nested expressions, but they may have different **associativity**:

- left-to-right: :cch:`x / y / z` is equivalent to :cch:`(x / y) / z`
- right-to-left: :cch:`x = y = z` is equivalent to :cch:`x = (y = z)`

For binary operators, there is a syntax sugar available when you want to perform assignment to the first of the operands:

- :cch:`x += y` is the same as :cch:`x = x + y`.
- :cch:`x *= y` is the same as :cch:`x = x * y`.
- :cch:`x %= y` is the same as :cch:`x = x % y`.
- and so on...

Much later, you will also learn about **operator overloading**. Because most built-in operators work only with built-in types, C++ allows to define meaning for operators when user-defined types are involved. You have already used overloaded :cch:`operator<<` with :cch:`std::cout`.

Comparison
##########

- less than: :cch:`x < y`
- less than or equal: :cch:`x <= y`
- greater than: :cch:`x > y`
- greater than or equal: :cch:`x >= y`
- equal: :cch:`x == y`
- not equal: :cch:`x != y`

All them produce a value of type :cch:`bool`.

.. admonition:: warning
    :class: warning

    Do not mistake ``==`` wih `=`:

    - ``=`` is the assignment operator. :cch:`x = y` assigns value of :cch:`y` to :cch:`x`.
    - ``==`` is the equality operator, :cch:`x == y` produces a value of type :cch:`bool` informing whether operands are equal.

Arithmetic
##########

There are 5 basic arithmetic operators: ``+``, ``-``, ``*``, ``/``, ``%``. All can be used on integer types and all except ``%`` can be used on floating-point types.

.. admonition:: note
    :class: note

    There is no operator for powers. :cch:`x ^ y` does not raise :cch:`x` to the power of :cch:`y` but performs *bitwise XOR* instead. Powers and other mathematical operations can be done using functions from the standard library.

Arithmetic expressions can generate different machine code depening on types of used variables. Math is done very differently on integer and floating-point types.

Since you are learning programming I'm pretty sure you are already familiar with math, but there are some special situations which you should understand - while math is flawless reality has its limitations.

Integer operations
##################

Integer division is done ... on integers. The result is also an integer so any fractional part is lost. If you want the remainer, use modulo (``%``).

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x = 22;
        int y = 5;

        int quotient = x / y;
        int remainder = x % y;
        std::cout << "quotient: " << quotient << "\nremainder: " << remainder << "\n";

        // this should always print x
        std::cout << "reversed operation: " << quotient * y + remainder << "\n";
    }

.. admonition:: warning
    :class: warning

    Integer division and modulo where second operand is zero is undefined behavior.

The above warning should be self-explanatory. Such operations have no definition in mathematical world, and the same happens in C++. If you perform these operations and can not guuarantee what the second operand is (e.g. it's provided by the user of the program) you should definitely check it to prevent any potential bugs.

Overflow
========

If the result of the operation can not be represented (e.g. multiplication of 2 large integers produced value that does not fit in range)

- for signed integers: the behavior is undefined
- for unsigned integers: the value wraps around

Previously it was said that operations on signed and unsigned integers can be done using the same circuit - and this is still true for most hardware. C++ defines them differently though.

When overflow happens, the value wraps around. A good analogy is an odometer or a clock. The set of possible values is finite and there is a continuity between lowest and highest value.

.. image:: https://upload.wikimedia.org/wikipedia/commons/5/53/Odometer_rollover.jpg
    :alt: odometer rollover

During overflow, the most significant digit is lost. In binary system, the wrapping happens at powers of 2 - for an 8-bit integer adding 1 to ``1111 1111`` (255) would make it ``1 0000 0000`` so after discarding excess digit, it becomes ``0000 0000`` (0).

- For unsigned integers, this behavior is very desirable. Various formulas intentionally use wrapping behavior to form cycles or some pattern of repetition in output. Cryptography, hashing, control checksums and compression are very prominent users of overflow wrapping.
- For signed integers, the behavior has no good use because the lowest representatable value is not zero, but some negative number. So instead of starting over from zero, it starts over from some huge negative value. Such behavior has no practical use. Even worse, it's a very good source of bugs, most commonly found in games. If players find an overflow bug within a tycoon-style game, they can try to form a construction so expensive that its total cost overflows, which then causes the cost to be negative which then causes the game to subtract negative amount of in-game currency from their inventory, effectively giving them money instead of spending it.

Undefined behavior gives the compiler infinite freedom for optimization. Since anything can happen, any machine code will be fine as long as other requirements are fulfilled. This lets compilers optimize away code like :cch:`if (x + 1 < x)` as the only situation in which the statement could be triggered is overflow. If :cch:`x` is a signed number, compiler can assume overflow never happens (programs should be free of undefined behavior) and remove dead code.

    But who would write such nonsensical code?

It happens more often than you think. This example is very trivial, but once you start using more complex abstractions you will realize how easy it is to accidentally create such situations. The other thing is that you are still at the beginning of the tutorial so I can't really provide more complex examples.

You can see the difference on `compiler explorer <https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlJvoCqAZ0wAFAB4gA5AAYppAFZdSrZrVDIApACYAQjt2kR7ZATx1KmWugDCqVgFcAtrS6dSV9ABk8tTADlnACNMYhAADlIAB1QhQnNaO0cXN2jY%2BLofP0CnELDI40xTBIYCZmICJOdXTndC4rpS8oIsgODQiKMyiqqU2q7m1py8iIBKI1QHYmQOKSDUewBqKk4IOOA/dEXxUc0ZAEFNAHZ9A8XzxeJMAinabcWDRc4HgGYbbc0X08OjgBE9w4HeZLKjaCAOWjrTbbXYHY7fC6Xa63e6PZ6fd7iT7fY6/KTjVjSACs8lcsnkqGkNgMjyEk2mmAe2henHkBGkclG4wA1iBuNoAHQyF4ANiJRJeRO03HCMm4nEihKk3FJHIp0nkQhAMlI7PJ4zgsBgiBQqCcUTw7DIFAgaHNlo6wCEtGYUSECFQBD4loIoS1ECCatIQV85QAntJWaQ7U4rAQAPK0VgR8mkLBONTAdhB/BXYoAN0wWtTmHERQcvsj8l8vqVchUeCCxHDdiwQYIxDwTir434jBY2Z4fDoBGEYkkqaU7lU6hQNL0DaCWsg41QUTMdGLAFohAR0J9flo9AZtDJFlv4y9NZgTBvXBBPL0ah5rEN2mF3DE4nen8ovxlaDfXIOjqG8ijvJoensaplHqCDuhaXw2mAj8Big5Jn13QYkOGEDxjpKYZi4AliVVVNKSkcRwhFLcRW4RZgGQZBFggDsIW5UYWNwQgSCZFlSEWOx7StPjOE46ljz0Nk1S5UheSJHUlRVUhuyJTgBXlBUAE4jiOLSRW0QyXhkEVSDJesKM1bVdRk0hDRNO0LStchKEch0wmQGdgAAfTY2huW9VhfWIf1A1TEMXWIFMoxjONE2THNMAzdRs1TXNwLwQti3rUty0rKQoxrG8g1YRtmyi1tZnrDsux7Yd6CYNgOCHPsxwkIMlG0FRMznSTDFKpd4FXdcEm3Xd9xeQ9510U9z0va9bwSSxrF/dxPCAkZP3SH9oL6NJvwSDaQKMMCGloSDKl2zDTvg7DsnfWCENWtDEPulDiImQjmpIqQSTMoMKKomi6MWTzMxYvyOK4/AiGIUSBKEpzQj47RxOm6T9R%2B5TuxlAUiXCcJOBkQzhV0o4RS0/7yI1IxrL1TkeRAIkjgFfSXm4bg6KONStPxrqlSvKmLJp%2Bn8R%2B7QyOFqQMYZ0hCxCpbuCAA%3D>`_ - functions are almost identical; the one operating on signed integer doesn't do any comparison in its machine code.

Overflow is reversible:

.. cch::
    :code_path: 08_operators/overflow.cpp
    :color_path: 08_operators/overflow.color

.. the example above should not use uint8_t because it usually is an alias for unsigned char and prints value as text instead

Summing it up:

- Overflow on unsigned numbers is well-defined in C++ because underlying hardware behavior is useful.
- Overflow on signed numbers is undefined in C++ because it's not useful and making it undefined gives more freedom for optimizations.

...and for this reason:

.. admonition:: tip
    :class: tip

    Unless you need wrapping behavior or perform specific bit-level operations, you should always use signed integers, even if input data is never negative.

Floating-point operations
#########################

Unlike with integers, there is no way for undefined behavior to occur during floating-point arithmetic. In bad situations, you will end up with special values instead:

- Division by zero will result in positive or negative infinity, depending on signs of operands.
- Overflow-wrapping can not happen. Intead, results will get stuck on positive or negative infinity.
- Nonsensical operations (zero divided by zero, square root of negative number, logarithm of negative number, etc.) will result in NaN (not-a-number).
- Any operation where one of operands is NaN will always result in NaN.
- Some of these operations can raise *floating-point exceptions*. These are not *C++ exceptions* (it's a very different thing) and shouldn't concern you now.

Many operations with floating-point types are affected by `floating-point environment <https://en.cppreference.com/w/cpp/numeric/fenv>`_. This is usually a set of CPU settings that affect current thread. Compiler options can also change the environment. This information shouldn't bother you now though, knowledge what happens in typical bad situations (listed above) is much more important.

Underflow
=========

First, some clarity as this term often gets misunderstood. There is a common mistake where going below minimum representatable value is referred to as underflow.

.. admonition:: error
    :class: error

    During integer arithmetic, if the result is larger than maximum representatable value, **overflow** happens. If the result is smaller than minimum representatable value, this is also **overflow**.

    - **Overflow** happens with integers when value does not fit in range.
    - **Underflow** happens with floating-point when value is truncated to zero.

Underflow occurs when the value is so small that the closest representatable value is zero. The following program continuously divides the same variable untill its value underflows:

.. cch::
    :code_path: 08_operators/underflow.cpp
    :color_path: 08_operators/underflow.color

More floating point shenanigans
===============================

If you are really interested about floating-point, I recommend you to watch `CppCon 2015: John Farrier - Demystifying Floating Point <https://www.youtube.com/watch?v=k12BJGSc2Nc>`_. The presentation goes over many peculiarities and gives insight into various solutions. Knowing these is what separates good programmers from the best programmers.

Short summary of key points in the presentation:

- Normalize values to range -1 - 1. Calculations in this range have highest precision.
- Use formulas which don't mix big numbers with small numbers. Separate big with big and small with small operations will achieve more accurate results.
- Don't ever compare floating-point directly as their equality (except with zero) is basically unachieveable. Instead, make comparisons within +/- epsilon tolerance from expected result.
- If you aren't sure, prefer multiplication over division (``x / y`` can be refactored to ``x * (1 / y)``). It's usually more precise and faster.
- Avoid accumulation of bias: instead of adding a floating-point constant after every iteration, count number of iterations (as integer) and multiply it with the constant.
- Check how your hardware treats `denormal numbers <https://en.wikipedia.org/wiki/Denormal_number>`_. Some may feature 100x slowdown in which case you might prefer to change settings to perform underflow.

Logical operators
#################

3 logical functions are available:

- negation (NOT): :cch:`!x`
- conjunction (AND): :cch:`x && y`
- disjunction (OR): :cch:`x || y`

All of them operate on and produce values of type :cch:`bool`.

Equality operators (``==`` and ``!=``) work on various types but if they are used on values of type :cch:`bool` then ``==`` is also equivalent to NXOR function and ``!=`` is also equivalent to XOR function.

Bit negation
############

``~`` flips all bits. This operator is unary.

.. cch::
    :code_path: 08_operators/bit_negation.cpp
    :color_path: 08_operators/bit_negation.color

.. admonition:: note
    :class: note

    Binary literals require C++14.

.. admonition:: note
    :class: note

    The bitset type is used to change output from printing integers to printing bit representations. More on how to manipulate output - in later lessons.

.. admonition:: tip
    :class: tip

    Remember to use unsigned types for any kind of bit operations.

Bitwise operators
#################

These operators apply specific logical function bitwise. That is, for 2 inputs, each having the same amount of bits, each of the output bits is a result of separate logical function applied to consecutive pairs of input bits.

.. cch::
    :code_path: 08_operators/bitwise.cpp
    :color_path: 08_operators/bitwise.color

Bit shift operators
###################

Move bits left or right. Bits going out are discarded and new bits are 0s.

.. cch::
    :code_path: 08_operators/bit_shift.cpp
    :color_path: 08_operators/bit_shift.color

This is also a good example how the same operator (``<<`` and ``>>`` in this case) can perform different task depending on what it's being used with (here: bit shifts and stream insertion).

.. admonition:: warning
    :class: warning

    Bit shifts are undefined behaviour:

    - when right operand is negative
    - when right operand is larger than the amount of bits in the left operand
    - in some combinations when the left operand is a signed integer - too complex to list but you shouldn't use signed integers for bit operations anyway

..

    Why such simple operation can result in undefined behavior?

Short answer: optimization. Long answer: some 1 hour long CppCon video that I can't find.

Other operators
###############

Not all operators are written using symbols. Many C++ operators are keywords. There are 2 very simple unary operators which return memory-related properties:

- :cch:`sizeof` - returns the size in bytes of specific type
- :cch:`alignof` - returns the alignment in bytes of specific type

Both always return a non-zero integer of type :cch:`std::size_t`.

Alignment affects placement of objects in memory. For simplest types, its value will usually be the same as size. Explaining it in detail would take some time and would require more knowledge about memory so I'm only mentioning it as an operator example.

.. cch::
    :code_path: 08_operators/other.cpp
    :color_path: 08_operators/other.color

..

    Why is size of :cch:`bool` equal to 1? Shouldn't it be a single bit? Is it because the operator returns size in bytes?

When stored in memory, :cch:`bool` will occupy a full byte [1]_. This is for multiple reaons:

- Memory is addressed by bytes, not bits. It's not possible to fetch a single bit.
- Multiple :cch:`bool`\ s could be packed in a byte but then saving and retrieving single bit information would unnecessarily complicate machine code, slowing down the program.
- Higher memory usage does not necessarily mean worse performance. Vast majority of today's software prefers to sacrifice memory for faster execution. Most of the time, there is a lot of free memory but the processor is highly utilized.

In some cases, the compiler can optimize :cch:`bool` to a single bit (more precisely, a single CPU flag register). These cases are usually comparisons where the value of type :cch:`bool` is never stored, only immediately used for an :cch:`if` (or similar) statement.

    Do these operators have actual use or are they just a way to obtain implementation-defined details?

They have use in raw memory operations. Such operations work on a lower abstraction layer than most of C++ type system and information they provide is crucial in these operations.

Recommendations
###############

Precedence
==========

Some operators have higher priority than others. Because C++ has over 40 different operators, no one remembers their precedence perfectly - only some of them are strictly related to math. Things can get complicated once multiple very different operators are used in one expression.

Therefore, it's highly recommended to wrap complex subexpressions in parentheses:

.. cch::
    :code_path: 08_operators/precedence.cpp
    :color_path: 08_operators/precedence.color

This will make reading code easier while also saving you some time from dealing with unexpected bugs.

Spacing
=======

It's intuitive for unary operators to have higher priority than binary operators: `x + !y` is processed as `x + (!y)`. While whitespace characters doesn't matter in this case, it's highly recommended to write spaces around binary operators and stick unary operators to their arguments.

.. cch::
    :code_path: 08_operators/spacing.cpp
    :color_path: 08_operators/spacing.color

In other words, operators which are applied first should be closer to the object.

----

.. [1] Unlike character type, size of boolean type is actually implementation-defined but I haven't heard of any implementation which would differ from 1 byte. There are no reasons to do otherwise.
