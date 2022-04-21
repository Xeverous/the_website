.. title: 03 - recursion
.. slug: index
.. description: recursive functions
.. author: Xeverous

In the previous lesson you have seen 2 functions which call each other. Such thing can also happen for a single function.

.. admonition:: note
    :class: note

    To understand recursion, you must first understand recursion.

This is a known joke but it still delivers an important concept: **recursion is the act of referring to itself**.

Recursion is a very broad concept, mostly used in mathematics and computer science but other examples are also present such as https://en.wikipedia.org/wiki/Wikipedia.

Factorial
#########

Factorial is a prime example of a recursive function. It's definition can be written in multiple ways, including:

- iterative: ``n! = 1 * 2 * 3 * ... * (n - 2) * (n - 1) * n``
- recursive: ``n! = 1 if n = 0, n * (n - 1)! otherwise``

Both of these can also be expressed in code:

.. cch::
    :code_path: factorial.cpp
    :color_path: factorial.color

.. admonition:: note
    :class: note

    Recursive functions do not need forward declarations.

Depending on applied compiler optimizations, these 2 function definitions can result in different machine code.

- The iterative version could multiply numbers at each iteration of the loop.
- The recursive version could multiply numbers each time a previous call returned its result.

The core idea behind recursive functions is *divide and conquer* strategy. Each call does a single step (in case of factorial - multiplication) and mixes the partial result with the result of a slightly different call (in case of factorial - parameter is lowered by 1). There must be at least 1 situation in which the function does not recurse (the *base case*) (in case of factorial - paramater of value zero). A recursive function should never call itself with exactly the same input - this would mean an endless cycle.

Fibonacci
#########

Each number in the Fibonacci sequence is the sum of 2 previous numbers: 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...

Just like factorial, the function can be defined in both iterative and recursive ways:

.. cch::
    :code_path: fibonacci.cpp
    :color_path: fibonacci.color

Recursion vs iteration
######################

- When a function calls another function at its end, it's known as *tail call*.
- When a function calls itself at its end, it's known as *tail recursion*.

Compilers have special optimizations for tail calls. Their main purpose is to avoid adding new *stack frames* to the *call stack* because if the tail call is the last thing a function needs to do, there is no reason to return to the function when the nested call finishes. Instead of pushing new stack frame, machine code performs a jump to the beginning of the function. This creates a loop which reuses current stack frame and works on the same memory. Factorial function is not tail recursive because it needs to perform multiplication after nested call returns (though it could be modified to be tail-recursive).

All of recursive functions can also be written in iterative form. The iterative form is very often faster because calling a function recursively requires some overhead for each call (pushing new stack frame). Additionally, a good iterative implementation can optimize out redundant calculations - in case of recursive Fibonacci implementation you can notice that some function calls might happen multiple times: ``F(5) = F(4) + F(3) = F(3) + F(2) + F(2) + F(1)``. Since recursion does not save the result anywhere, it's being lost and recomputed multiple times. Iterative version stores 2 previous results. Some implementations can go even further as having a table (an array) of precomputed results for common inputs.

In practice, both iterative and recursive approaches have their place. Various algorithms are inherently recursive and refactoring them to iterative versions can be hard. Recursive functions can also have state - shared state is usually passed through parameters. Which approach to use is usually dictated by convenience.

Recursive main
##############

C++ standard explicitly forbids to call main function, thus it can not be recursive, even indirectly through a different function.

Summary
#######

- Recursive function is a function that calls itself.
- Recursive functions do not require forward declarations.
- Recursive functions must have some stop condition, otherwise they will form an endless cycle and freeze the program.
- Usually iterative versions of recursive functions are faster and consume less memory.
