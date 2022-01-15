.. title: 06 - loop control
.. slug: 06_loop_control
.. description: more on controlling loops
.. author: Xeverous

Apart from :cch:`break`, there is one more statement that can control the loop.

Continue statement
##################

:cch:`break` jumps outside of the loop. :cch:`continue` jumps to the end of current iteration (step statement is still executed).

The example below prints combinations of numbers but only if they are different.

.. cch::
    :code_path: 06_loop_control/continue.cpp
    :color_path: 06_loop_control/continue.color

The same behavior could be achieved with :cch:`if` statements alone, but :cch:`continue` is better because only this keyword is nested inside :cch:`if`, not the whole loop body. Less nesting generally means more readable code.

Exiting nested loops
####################

:cch:`break` can be used to exit a loop (the most enclosing one). But how to exit nested loops? Some languages offer such feature by extending syntax of the :cch:`break` keyword, usually by allowing labels or numbers (how many scopes to exit). There is no such thing in C++.

There are multiple alternatives:

- Use :cch:`goto`. Heavily discouraged because it breaks structured programming model.
- :cch:`throw` an exception. Heavily discouraged because exceptions should be used only for error handling, never for control flow.
- Use a :cch:`bool` variable as a flag.
- Exit the entire function by a :cch:`return` statement.

Because of the mentioned rationale, only last 2 are used in practice.

Flag variable
=============

.. cch::
    :code_path: 06_loop_control/flag.cpp
    :color_path: 06_loop_control/flag.color

It works, but has multiple disadvantages:

- An extra variable is needed, which complicates code.
- Multiple :cch:`break` and :cch:`if` statements might be needed, which is another complication and a good source of potential bugs.
- The code has so many (unpredictable) relations between loop control variables and the flag that it might be hard to optimize.

In practice this way of dealing with nested loops is rarely used - usually only when due to program logic the loops already have to contain a flag variable and it can be reused.

Return statement
================

The preferred option, results in very clean code but it exits a lot more - the entire function.

.. cch::
    :code_path: 06_loop_control/return.cpp
    :color_path: 06_loop_control/return.color

In practice this is not a problem because loops can be easily moved to a separate function (to alter the scope of return statement), especially local function objects created by *lambda expressions*. Once you learn lambdas, you will understand how useful they are.
