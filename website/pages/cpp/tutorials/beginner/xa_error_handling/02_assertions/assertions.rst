.. title: 02 - assertions
.. slug: index
.. description: self-checks within a program
.. author: Xeverous

.. TOCOLOR

From Wikipedia:

    In computer programming, specifically when using the imperative programming paradigm, an assertion is a predicate (a Boolean-valued function over the state space, usually expressed as a logical proposition using the variables of a program) connected to a point in the program, that always should evaluate to true at that point in code execution. Assertions can help a programmer read the code, help a compiler compile it, or help the program detect its own defects.

    For the latter, some programs check assertions by actually evaluating the predicate as they run. Then, if it is not in fact true – an assertion failure – the program considers itself to be broken and typically deliberately crashes or throws an assertion failure exception.

In simpler words, an assertion will be a construct within code (usually something resembling a function call) that should always evaluate to true when invoked as control flow encounters it. Assertions are a form of self-checks made by the program itself, to ensure it's running correctly.

In C++
######

C++ offers 2 kinds of assertions:

- the :cch:`assert` macro which comes from the C standard library (a configurable runtime assertion)
- :cch:`static_assert` (a compile-time assertion)

:cch:`assert`
#############

The program below contains an assertion which prevents it from invoking undefined behavior. The macro has ugly name (not UPPERCASE as macros are suposed to have) because it's very old, from early C times.

.. cch::
    :code_path: example_assert.cpp
    :color_path: example_assert.color

How the macro works:

- if :cch:`NDEBUG` is defined: the macro expands to an empty statement, as if nothing was written (as if the statement was completely commented out).
- if :cch:`NDEBUG` is not defined: expands to a statement that evaluates given expression:

    - if :cch:`true` then nothing happens.
    - if :cch:`false` outputs implementation-defined diagnostic information on the standard error stream and calls :cch:`std::abort`, which terminates the program. The diagnostic message is guaranteed to contain the source code from the expression (turned into text by preprocessor stringization - :cch:`#`), :cch:`__FILE__`, :cch:`__LINE__` and :cch:`__func__`.

Why weird NDEBUG ("not debug") name? Just history. NDEBUG is never defined within standard library but high-level build tools (e.g. CMake, Meson) and IDEs have the concept of relase and debug build configurations. Pretty much all such tools will add ``-DNDEBUG`` (or equivalent) to compiler flags in release configuration to disable the macro in release builds (C++ does not define this macro by default). Many libraries offer similar macro, sometimes implemented as a wrapper around the standard one.

A quick test with the program above can result in something like this:

.. code::

    main.cpp:6: int divide(int, int): Assertion 'y != 0' failed.

.. admonition:: note
    :class: note

    As of writing this, MSVC implementation does not conform to C++11 requirements - the diagnostic message does not contain :cch:`__func__`.

    libstdc++ implementation (used by GCC and optionally by Clang) uses :cch:`__PRETTY_FUNCTION__` extension instead of :cch:`__func__`, which outputs a lot of details about the function (return type, argument types, template parameters), not just its name.

Custom diagnostic message
=========================

The macro takes only 1 argument which is the condition and while it outputs a message there is no dedicated place for additional text. However, a custom message can be added thanks to some evaluation tricks. Common ways of improving :cch:`assert` macro:

.. cch::
    :code_path: assert_msg.cpp
    :color_path: assert_msg.color

The first trick uses the fact that ``,`` is an operator that evalues both operands but returns the value of the second (of the last operand if chained). For example, :cch:`(1, 2, 3)$$$(num, num, num)` returns :cch:`3`.

- An extra set of parentheses is added to force evaluation through this operator. Otherwise the :cch:`assert` macro would error it got 2 arguments but expected 1.
- The order of condition and message is flipped so that the condition is evaluated for the assertion.
- Message is cast to :cch:`void` to shut "operand of comma operator has no effect" warning.

The second trick relies on implicit convertions.

- The macro uses the fact that ``x AND true`` is equivalent to ``x``.
- The string literal is an array which will *decay* to a non-null pointer (every string has a non-zero address) which when converted to :cch:`bool` will always be :cch:`true`.
- The condition is placed in parenthesis to guard against possible changes of meaning due to operator precedence.

..

    Can I use a variable to hold the message and put the variable in the macro?

You can, but ... the macro will print variable's name, not its value. For this to really work you would need a very different implementation of the macro, one that passes the variable to some output function.

`Boost.Assert <http://boost.org/libs/assert>`_ library offers an upgraded version of the macro similar to the one presented above. Additionally, it has more compile-time enable/disable switches as well as ability to implement custom assertion failure handler.

Side effects
############

An assertion should never have any side effects. They are not present in release builds so the program must work the same with and without them.

A hypothetical program loads its configuration and puts entries of the same type into an array. Then, just before they are used, an assert is placed to ensure there are no duplicate entries:

.. code::

    // at the end of configuration loading
    assert(!has_duplicates(entries));

    // elsewhere - function definition
    bool has_duplicates(std::vector<config_entry>& v)
    {
        std::sort(v.begin(), v.end());
        // after sorting, duplicate elements would be next to each other
        return std::adjacent_find(v.begin(), v.end()) != v.end();
    }

This isn't a good assertion because it has a side effect. If the assert is present (even if it does not fire) executing it will sort the vector. This doesn't seem to affect program state immediately, but it could impact program performance differently in release and debug builds aswell as change the order of processing configuration (which could have non-trivial consequences, depending on how it works).

What could be done to improve this code? If the program's configuration should always be sorted (e.g. because processing it requires certain order), the code could be modified as such:

.. code::

    std::sort(entries.begin(), entries.end());
    assert(!has_duplicates(entries));

    bool has_duplicates(const std::vector<config_entry>& v)
    {
        assert(std::is_sorted(v.begin(), v.end()));
        // after sorting, duplicate elements would be next to each other
        return std::adjacent_find(v.begin(), v.end()) != v.end();
    }

If sorting is not necessary, then the assertion could be written as in original example but with 1 difference - the function should take vector by value (copy) and then sort this vector. Sorting a copy would not affect original vector.

.. code::

    assert(!has_duplicates(entries));

    bool has_duplicates(std::vector<config_entry> v)
    {
        std::sort(v.begin(), v.end());
        // after sorting, duplicate elements would be next to each other
        return std::adjacent_find(v.begin(), v.end()) != v.end();
    }

..

    What if copying configuration entries had a side effect?

Then the program has even bigger problem - violation of one of OOP idioms. Object-oriented programming is much later in the tutorial but it should be relatively straightforward to understand that a copy is a copy - an independent second object, where operations on one should not affect the other.

.. admonition:: tip
    :class: tip

    Since all assertions should only read program state, you should be suspicious if a function used inside an assertion takes anything by non-const reference. Such code heavily suggests the object is being modified.

Static assertions
#################

:cch:`static_assert` does very similar job but at compile time. The keyword works similarly to a function and could be roughly represented as the following pseudocode:

.. cch::
    :code_path: static_assert.cpp
    :color_path: static_assert.color

The condition must be a constant expression, otherwise the program is ill-formed. The message can only be a string literal, that is, you must write quoted string where the assertion is present. You can not even use :cch:`constexpr` variables to hold the message. If you do not have C++17 and have no need for the message you can simply write :cch:`""`.

If the condition evaluates to :cch:`true` the statement has no effect. If :cch:`false`, a compile-time error is issued, and the text of message, if any, is included in the diagnostic message.

:cch:`static_assert` is commonly used within templates as it allows to ensure that various compile-time requirements are satisfied. When given invalid types or values, it's much better to get a compiler error with the message from failed assertion than a complex template error describing many details.

TOEXAMPLE good simple static assert example

Recommendations
###############

Assertions are intended to catch internal bugs within the program, during testing on debug builds. You should not use assertions to handle external problems such as input errors because they are not suited for handling them - assertions only catch invalid states and report them usually by very interrupting means (immediately stopping the program or throwing an exception).

Example good places to put an assertion:

- just before array access to check index validity
- inside an algorithm to ensure it's behaving correctly
- just before returing from the function to verify that the result meets intended criteria
- basically any operation that if not guarded against could cause UB
