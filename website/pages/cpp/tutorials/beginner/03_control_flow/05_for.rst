.. title: 05 - for
.. slug: 05_for
.. description: for loops in C++
.. author: Xeverous

Before diving into a for-loop and learning its purpose, you should learn a new operator first. Vast majority of its usage is inside for-loops.

Increment and decrement
#######################

A very simple but very handy operators:

- Increment is equivalent to :cch:`x = x + 1`.
- Decrement is equivalent to :cch:`x = x - 1`.

These operators come in 2 forms:

- prefix: :cch:`++x`, :cch:`--x`
- suffix: :cch:`x++`, :cch:`x--`

Both modify the value by adding or subtracting 1, but the difference lies in what they *return*. Prefix versions behave in-place, suffix versions modify the variable but they *return* old value:

.. cch::
    :code_path: 05_for/increment.cpp
    :color_path: 05_for/increment.color

For suffix version you can see that it does change the variable but its result is not visible in the same statement.

.. admonition:: tip
    :class: tip

    Prefer prefix version of increment and decrement. It's simpler and more optimal.

Suffix versions are usually used inside more complex statements, where a specific index must be incremented/decremented after every operation.

    What happens when operators are used multiple times in the same statement?

If they apply to the same object - nothing good. In such cases the behavior is unspecified or undefined.

.. cch::
    :code_path: 05_for/increment_ub.cpp
    :color_path: 05_for/increment_ub.color

.. admonition:: tip
    :class: tip

    For any variable that is incremented/decremented, it should appear only once within a single statement.

Trivia
######

The ``++`` and ``--`` operators appeared already in early C. A new, more advanced programming language was forming but had no widely recognizable name ("C with classes" was too long, "new C" was't precise). The current name is credited to Rick Mascitti who in 1983 came up with the idea to use C++ as a symbolic improvement over C.

The for-loop
############

:cch:`for` doesn't bring any new functionality over :cch:`while`, but it offers significant syntax improvement, especially if you want a variable only for iteration.

The program below prints numbers in range 0-9 using 2 different loops. Both loops are equivalent.

.. cch::
    :code_path: 05_for/for.cpp
    :color_path: 05_for/for.color

The for-loop (apart from its body) has 3 statements:

- intialization
- condition
- step

The step is executed after each iteration. The primary purpose of 2 additional statements is creation and modification of the loop control variable. **In almost all for-loops, intialization, condition and step all use the same variable and the body of the loop does not change it.**

.. admonition:: tip
    :class: tip

    When using :cch:`for`, the body of the loop should not change loop control variable.

By convention, the loop control variable is named ``i`` (from iteration or index). Nested loops typically use next alphabet letters (``j``, ``k``, ...). If the code works with mathematics or any sort of 2D/3D data the variables might be named ``x``, ``y``, ``z`` or ``u``, ``v``.

    What if I don't need a new variable and/or a step statement?

Then you still need to write ``;``. The simplest (infinite) loop is then :cch:`for (;;)`. In such case (no loop control variable needed) you should use :cch:`while`.

Nested loops
############

Nested :cch:`for` loops are very common when dealing with any multidimentional data. Suppose you would like to have such output:

.. code::

    1
    1 2
    1 2 3
    1 2 3 4
    1 2 3 4 5

To print each line, you could think of something based on this:

.. cch::
    :code_path: 05_for/for_repeated.cpp
    :color_path: 05_for/for_repeated.color

Now you can notice a repetition within these loops. The full solution is:

.. cch::
    :code_path: 05_for/for_triangle.cpp
    :color_path: 05_for/for_triangle.color

Note when the line break is placed - it's only inside the first loop. When dealing with nested loops it's important to think what actions need to be done at which level.

Exercise
########

Write programs that print these (each can have multiple solutions):

.. code::

     0  1  2  3  4  5  6  7  8  9
    10 11 12 13 14 15 16 17 18 19
    20 21 22 23 24 25 26 27 28 29
    30 31 32 33 34 35 36 37 38 39
    40 41 42 43 44 45 46 47 48 49
    50 51 52 53 54 55 56 57 58 59
    60 61 62 63 64 65 66 67 68 69
    70 71 72 73 74 75 76 77 78 79
    80 81 82 83 84 85 86 87 88 89
    90 91 92 93 94 95 96 97 98 99

.. code::

            5
          4 5
        3 4 5
      2 3 4 5
    1 2 3 4 5

.. code::

     1  2  3  4  5  6  7  8  9 10
     2  4  6  8 10 12 14 16 18 20
     3  6  9 12 15 18 21 24 27 30
     4  8 12 16 20 24 28 32 36 40
     5 10 15 20 25 30 35 40 45 50
     6 12 18 24 30 36 42 48 54 60
     7 14 21 28 35 42 49 56 63 70
     8 16 24 32 40 48 56 64 72 80
     9 18 27 36 45 54 63 72 81 90
    10 20 30 40 50 60 70 80 90 100

.. TODO unlock fizzbuzz article?
.. TODO post idiomatic solutions
