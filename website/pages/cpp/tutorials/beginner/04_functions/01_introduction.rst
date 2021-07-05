.. title: 01 - introduction
.. slug: 01_introduction
.. description: introduction to functions
.. author: Xeverous

You definitely have encountered the *function* term before. It's very likely you already have a rough image what a function is.

In mathematics, a function is a relation between two sets that associates each element of the first set to exactly one element of the second set.

In programming, a function is a reusable piece of code that given certain set of inputs *returns* (produces) an output (an object).

In both mathematics and programming:

- A function always *returns* a single value. No matter how many inputs a function gets, it always produces a single output.
- A function can *return* the same value for multiple, different inputs. For example, a square function *returns* 4 for both 2 and -2.
- A function may receive (invalid) inputs for which there is no result:

  - In mathematics: argument out of domain, logic error
  - In programming: any kind of error or undefined behavior

In programming:

- A function can return different value even if given the same input. For example, a date/time function can return different date/time each time it's *called* (used).
- A function can have side effects, they are never considered to be function's output.

.. admonition:: note
    :class: note

    Functions are one of fundamental programming elements. They allow to build complex programs while reducing code duplication. In practice, almost every function calls other functions forming deep chains of code reuse.

Syntax
######

Vast majority of functions are defined using the syntax below. Other ways (lambda expressions and member functions) will be presented later.

In order:

- return type
- function name
- function parameters
- function body

.. cch::
    :code_path: 01_introduction/syntax.cpp
    :color_path: 01_introduction/syntax.color

.. admonition:: note
    :class: note

    Unlike conditional statements and loops, a function body must always contain ``{}``.

.. admonition:: note
    :class: note

    Functions are called (used) by providing arguments between ``()``.

Functions create own scope for their local objects (objects defined inside functions), these objects are destroyed when the function returns - only returned value is retained. You have already used this rule - so far all code has been written inside main function.

Returning
#########

Returning is the act of providing function's result. The type of the object at the :cch:`return` statement should be the same as function return type or be implicitly convertible to it.

.. admonition:: definition
    :class: definition

    A function should never reach the end of its body without :cch:`return` statement.

The function below does not return on all control flow paths. If at runtime this function is called with zero, it will cause undefined behavior.

.. cch::
    :code_path: 01_introduction/missing_return.cpp
    :color_path: 01_introduction/missing_return.color

..

    Why such functions are allowed then? Can't the compiler check that a function can finish without returning?

The compiler can not analyze all possible operations and simulate all potential function usages - there are simply too many of them and many of them may be impossible or simply never happen. For these reasons, in the past it was generally accepted that a function may have hypothetical control flow path that results in reaching end of its body without hitting any return statement. Over time, it turned out that such approach is generally unsafe (bug prone) and results in code that is hard to read and reason about.

The new approach is simpler and more safe: **a function should cover all of its control flow paths (even if they seem to never be possible)**. The compiler can not simulate the function, but it simply checks whether all branches of any conditional instructions end in return statements. For backwards compatibility, C and C++ still allow functions with missing return statements, but compilers issue a warning.

Void functions
##############

Functions can have return type specified as :cch:`void` which means they return no data. This is very useful if the function is used for its side effects:

.. cch::
    :code_path: 01_introduction/void_return.cpp
    :color_path: 01_introduction/void_return.color

Such functions do not need to use :cch:`return` as there is no data to send back to the caller. If you want to exit such function prematurely, you can always write :cch:`return;`.

Function size
#############

There have been many guidelines on what's a good size for a function. 20, 50 and even 100 lines of code. **The core principle is that a function should perform exactly 1 task.** If you see an opportunity to split the task into smaller ones, do it even if the function is used only once. Such code is easier to read and test. Functions should be like Lego bricks - they should very easily compose into larger constructions and be easy to modify.

The same principle applies to the amount of function parameters. The reasonable maximum amount is 6, which should be used only for specific algorithms. The more parameters a function has, the harder it's to understand and the more likely a bug can happen and more likely the function can be refactored into multiple smaller ones.

There is no lower limit on size and arguments. Many useful functions can be as simple as 1 line:

.. cch::
    :code_path: 01_introduction/one_line.cpp
    :color_path: 01_introduction/one_line.color

Recommendations
###############

- Unless there is a better reason, function parameters should be ordered in decreasing importance (most important parameters first).
- Variables are data. Functions are algorithms. Variables should be named as nouns and functions as verbs.
- Before you write a function for some task, check whether it's not already in the standard library. A lot of common mathematical operations are already available in `cmath header <https://en.cppreference.com/w/cpp/header/cmath>`_.

Exercise
########

- Compile the function with missing return statement and observe any compiler warnings. Don't try calling it - you should never expect anything meaningful from undefined behavior.
- Remember Collatz conjecture from control flow chapter? Now write a function that given a number, returns the next number. Modify the program from that lesson to use this function.
