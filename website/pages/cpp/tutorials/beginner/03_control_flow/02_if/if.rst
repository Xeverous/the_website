.. title: 02 - if
.. slug: index
.. description: if statements in C++
.. author: Xeverous

.. TODO explain std::cin before this lesson

The simplest control flow keywords of them all - :cch:`if`. It executes attached code only if the condition is :cch:`true`.

.. cch::
  :code_path: if.cpp

Comparisons naturally produce values of type :cch:`bool` but the condition can be any expression that is or can be converted to a value of type :cch:`bool`. :cch:`if` works as an explicit convertion so objects which require explicit convertion will also work.

The negative branch can be introduced with :cch:`else`:

.. cch::
  :code_path: if_negative_branch.cpp

..

    What if I want only negative branch?

Simply reverse the result. You can use ``!`` to flip a boolean but often you can just modify the condition to produce reversed result:

.. cch::
  :code_path: reverse_condition.cpp
  :color_path: reverse_condition.color

You can omit braces (``{}``) if exactly one statement is used:

.. cch::
  :code_path: no_braces.cpp
  :color_path: no_braces.color

.. admonition:: tip
    :class: tip

    Be consistent with your choice for braces. If you do both positive and negative branch, either use braces for both or none.

.. admonition:: tip
    :class: tip

    If the code on any branch of :cch:`if` has more than 1 line (e.g. very long statement that has been split to 2 lines or a 1-line statement + 1-line comment) **always use braces, even if you can skip them**. Reason: code readability. In other words, be consistent - apply braces to both branches or none.

Some projects take the rule even further and always require braces, even for simplest and shortest 1-line statements - the argument for it is safety as braces prevent situations like this:

.. cch::
  :code_path: misleading_indentiation.cpp

The above program will print that :cch:`x` is both even and odd. The problem is that code has been written assuming that the :cch:`else` will attach to the first :cch:`if` statement, but it attached to the second - formatting does not affect language grammar. Some compilers may print a warning that the code is misleadingly indented:

.. ansi::
    :ansi_path: misindent.txt

.. admonition:: tip
    :class: tip

    If you nest :cch:`if` statements, you can omit braces only on the deepest level.

This is the minimum to make the code work and be consistent:

.. cch::
  :code_path: misleading_indentiation_fixed.cpp

Sometimes, thanks to many conditions your code might indent very deeply, like this (image shows PHP, not C++):

.. image:: https://i.imgur.com/BtjZedW.jpg
    :alt: code Hadouken

There are ways to solve such problems. One of them does not require any additional features so I can present it to you now. If you have an if-else tree that nests only on one end like this:

.. cch::
  :code_path: if_tree.cpp

...then you can use the rule that allows a single statement without braces and format the code in a very compact way:

.. cch::
  :code_path: if_tree_compact.cpp

Here braces are not only ommited for print statements, but they are also ommited between :cch:`else` and :cch:`if` keywords.

Syntax sugar
############

Since C++17 it's possible to have an extra statement inside :cch:`if`, before the condition. It's very useful if you need to perform extra work but also limit the scope of any extra objects:

.. cch::
  :code_path: cpp17_syntax.cpp
  :color_path: cpp17_syntax.color

The code is equivalent to:

.. cch::
  :code_path: cpp17_syntax_equivalent.cpp
  :color_path: cpp17_syntax_equivalent.color

Ternary conditional
###################

There is a special ternary (arity of 3) operator that is similar to :cch:`if` but it works on the expression level, not statement. This makes it possible to use it as a subexpression inside complex statements:

.. cch::
  :code_path: ternary_print.cpp
  :color_path: ternary_print.color

and to simply else-if code:

.. cch::
  :code_path: ternary_if_else.cpp
  :color_path: ternary_if_else.color

The ``?:`` operator must always have 2 branches. You can get very creative with its usage (it works as a functional subexpression, not as a full statement) (not only for assignments) but I advise you to not overuse it because (due to grammar and backwards compatibility) `its evaluation rules <https://en.cppreference.com/w/cpp/language/operator_other#Conditional_operator>`_ have gone extremely complex.

Advanced example
################

Sometimes it might not be obvious how large simplifications are possible. The example below has a space for multiple potential improvements.

.. cch::
  :code_path: example_advanced.cpp
  :color_path: example_advanced.color

Note that the result of the function is wanted in both branches - the first branch (before improvements) used a local variable to avoid duplicate function calls but this resulted in hiding of the redundancy.

.. cch::
  :code_path: example_advanced_fixed.cpp
  :color_path: example_advanced_fixed.color

Exercise
########

Question 1
==========

What's wrong with the following code?

.. cch::
  :code_path: exercise_q1.cpp
  :color_path: exercise_q1.color

.. details::
    :summary: Answer

    There are 2 mistakes:

    - There is ``;`` immediately after the condition (null statement) which acts as the braceless one statement. It will prevent actually intended statements from happening and break the :cch:`else` (either shifting it to a different :cch:`if` or making a compiler error).
    - There are 2 branches but the condition contains a negation. It can be simplified by reversing the condition and swapping branch bodies:

    .. cch::
      :code_path: exercise_a1.cpp
      :color_path: exercise_a1.color

Question 2
==========

What's wrong with the following code?

.. cch::
  :code_path: exercise_q2.cpp
  :color_path: exercise_q2.color

.. details::
    :summary: Answer

    The code uses ``=``, not ``==``. This will cause the assignment to take place and because assignment operator returns first operand (it's right-to-left associative) the :cch:`if` statement will evaluate :cch:`x` after the assignment (converting it to :cch:`bool`). All major compilers should warn on this type of mistake.

    .. I have considered to mention Yoda conditions but IMO their benefits are too low. They are rarely used, compilers detect accidental = well and Yoda conditons don't even work for all cases - only when one of operands is read-only.

    If both the assignment and the test are desired, major compilers agreed on this solution:

    .. cch::
      :code_path: exercise_a2.cpp
      :color_path: exercise_a2.color

..

    I don't get the *assignment operator returns first operand* part. What makes ``=`` compile inside :cch:`if`?

You need to understand that :cch:`if` does not see every entity inside the condition, it simply acts as a test of a value of type :cch:`bool`. The whole condition expression is evaluated first and only then its result is brought to the :cch:`if` logic. Why assignments *return* first operand as the result? This will get clearer once you get familiar with *functions* and the concept of *returning* a result - many parts of C++ work on the basis of functions and most operators (including ``=``) too.

Writing
=======

Write a simple pseudo-calculator program:

- The user should enter 2 numbers.
- The user should enter extra number specifying operation to perform (addition, subtraction, multiplication, division, modulus).
- The program should check validity of the operation (division and modulus by 0 have undefined behavior) and execute it if possible. Print the result.
