.. title: 06 - behavior
.. slug: 06_behavior
.. description: C++ program behavior
.. author: Xeverous

During some experiments, you might have made something like this:

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x; // uninitialized
        std::cout << "x = " << x << "\n"; // what will be printed?
    }

The variable has not been initialized. Compilers try to translate the source code as best as they can to optimal hardware instructions while following language specifications but because of C++ nature (full-spectrum programming language with no lower-level mechanisms hidden underneath) situations like this can happen.

This is an example of **undefined behavior**. It's unknown what will actually happen. Intuitively, the compiler will allocate memory for the variable, attempt to read it and send received bytes to operating system's standard output. What will these bytes contain? No idea. Most likely some garbage that was left after previous program which happened to use the same block of memory. The program above might print a different value every time it's run. Basically, C++ specification does not define what happens with reads of uninitialized memory so there are no guuarantees on the execution of this program.

If you try to compile this program, you might get a warning from the compiler about use of uninitialized object. Because compilers optimize code during many transformation steps from source code to machine code, programs containing undefined behavior might be deformed even further, amplifying problems. This is a very simple case but as the code gets larger and more complex, it gets really hard to predict and search for potential errors. Many optimizations transform machine code based on the assumption that the program has no bugs - if they didn't there would be no sense in optimizing malfunctioning code.

As a result, any C++ program containing undefined behavior can exhibit one or more of the following:

- unpredictable random crashes
- crashes under certain scenarios
- program freezes or slows down significantly
- program continues but does not behave as expected
- program works correctly (or at least seems to)

Basically, there are no limits on what can happen. For this reason, you should always try to make your programs free of undefined behavior.

Other behaviors
###############

C++ specification defines few more terms that describe different levels of guuarantees, but **only undefined behavior is the dangerous one**. Others just let the programmer rely more or less on certain things.

Unspecified behaviour
=====================

Behaviour that varies between implementations (mostly between compilers) but the conforming implementation is not required to document it.

This covers situations in which there is no single good answer. There are multiple valid solutions, you just don't know which one is used by the given implementation as it can depend on a lot of factors including applied optimizations, hardware characteristics and operating system decisions.

Example - in the expression :cch:`2 * 3 + 4 * 5` it's *unspecified* which multiplication is done first. As long as specification and mathematical laws are concerned, the only guuarantee is that the addition will be done last. But since both multiplications are independent, there is no obligation for the compiler to write machine code that performs them in certain order.

Unspecified behavior is mostly useful for optimizations because it allows some freedom for the compiler - usually being able to replace and/or reorder some machine instructions.

Implementation-defined behaviour
================================

Behaviour that varies between implementations (mostly between compilers) and the conforming implementation must document it.

Example: how many bytes :cch:`int` (and other types) occupy in memory.

This is mostly stuff which C++ standard can not precisely specify (as each hardware and system varies), but any compiler wishing to support C++ needs to make a consistent and documented decision.

A subset of implementation-defined behavior is *locale-specific behavior*, which is related to *locales*, a concept of settings related to time zone and language. A function outputting current date/time is a good example - everyone understands what it means but how exactly numbers and punctuation are used depends on the local language.

Well-defined behaviour
======================

The highest level of guuarantees, usually very precisely specified in the specification giving very little or no space for compilers to do it differently.

Best examples are all kinds of logical and arithmetic operations - math is everywhere the same.

Behavior vs diagnostics
#######################

There is one more concept related to behavior - diagnostics. C++ specification places requirements regarding certain errors - if they happen a conforming implementation is obliged to output an error (diagnostic message) **and reject compiling the program even if it could proceed**.

Such programs are called **ill-formed** and fall in one of two categories:

- ill-formed, diagnostic required
- ill-formed, no diagnostic required

For example, the :cch:`short long` type is ill-formed with diagnostic required. Even if the compiler could attach some meaning to it, the C++ standard forbids doing so to prevent accidental spread of incompatible and questionable code.

Some situations with ill-formed programs do not require diagnostic, usually because it's really hard to detect such problems and the standard does not want to force compilers into doing impossible or very costly analysis. In reality, compilers often do provide diagnostics even if not required, which increases overall safety but at the same time does not bind them in case situation changes (e.g. because new hardware works differently).

.. TODO as-if rule when?

Exercise
########

What can happen when executing a program with undefined behavior?

.. details::
    :summary: Answer

    Absolutely anything.
