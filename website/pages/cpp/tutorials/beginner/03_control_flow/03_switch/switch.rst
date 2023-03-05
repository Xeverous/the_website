.. title: 03 - switch
.. slug: index
.. description: switch statements in C++
.. author: Xeverous

:cch:`switch` is also a form of conditional statement but it has different rules regarding execution - it allows a *fallthrough* control flow.

The **fallthrough** behavior comes from the fact that unlike :cch:`if` or :cch:`else`, a :cch:`switch` statement can execute multiple sections of code based on a single condition. There is no positive/negative branch. There are only places where execution starts and stops.

Rules
#####

The syntax is slightly different from :cch:`if`:

- :cch:`if` requires a value of type :cch:`bool` (or something *contextually convertible* to it), :cch:`switch` requires a value of integral or enumeration type (or something *contextually convertible* to it).
- Each :cch:`case` must use a *constant expression* (it must be computable at compile time). :cch:`constexpr` objects satisfy this requirement.

Then, the expression in :cch:`switch` is evaluated once and compared for equality with cases in order of their appearance. It's not possible to make a different comparison (e.g. ``!=``).

Compile the following program and test how it behaves for different numbers:

.. cch::
  :code_path: switch_intro.cpp

The **execution starts on first matching case and then goes through all subsequent cases (fallthrough), without further testing for a match**. If you don't get it, try reordering cases so that values are no longer in descending order.

Said differently, a :cch:`switch` statement has no branches but a point where execution starts.

    Why case values have to be constant expressions?

Unlike if-else, :cch:`switch` (at least when it was introduced in C) was not only supposed to be a shorter version of if-else but also feature a specific optimization: jump table. The goal was to have only one condition which result affects a jump instruction, which then computes new memory address based on a table build up from constant expressions.

Today, compilers also perform this optimization on if-else blocks if possible.

    What does it mean that the expression inside :cch:`switch` is evaluated once?

It means that any code there will be run once. For example, :cch:`switch (func())$$$keyword (func())` will call the function only once, no matter how many cases are present. This is contrary to loops, where a condition is evaluated once per iteration.

Breaks
######

:cch:`break` is where the execution stops. In other words, it disables fallthrough.

.. cch::
  :code_path: switch_break.cpp

If you add a :cch:`break` to every statement then :cch:`switch` behaves the same way as if-else blocks:

.. cch::
  :code_path: switch_break_full.cpp

Default case
############

You can add a :cch:`default` case which will be executed if no other cases were matched (or if previous case allowed *fallthrough*). This is equivalent to the last :cch:`else` (with no condition) in an if-else sequence.

.. cch::
  :code_path: switch_break_default.cpp

Scope
#####

While :cch:`if` always introdues an inner scope the :cch:`switch` does not - all cases share the same scope. This can sometimes create problems because generally\ [1]_ transfer of control is not permitted to enter the scope of a variable.

.. cch::
  :code_path: scope_init_jump.cpp
  :color_path: scope_init_jump.color

To fix it simply introduce a scope:

.. cch::
  :code_path: scope_fixed.cpp
  :color_path: scope_fixed.color

Warning: no default
###################

Many compilers issue a warning when a :cch:`switch` has no :cch:`default` case (for a good reason) - usually it means that the programmer forgot to write code for when no :cch:`case` matches. If you actually want to do nothing if no case is matched, simply add a :cch:`default` case immediately terminated by a :cch:`break`:

.. cch::
  :code_path: warning_no_default.cpp
  :color_path: warning_no_default.color

.. admonition:: tip
    :class: tip

    It's much better to explicitly state that you want to do nothing than make others reading your code question if you have forgot to handle such situation.

Warning: fallthrough
####################

In practice, fallthrough is hardly ever desirable. Even if it is, people instinctively use a separate :cch:`if` earlier in the code which makes :cch:`switch` unneeded. For these reasons, compilers warn when fallthrough can happen - in almost all cases it's unintended.

If you really want to do fallthrough (and silence the warning), there are 2 ways:

- "fallthrough" comment (not all compilers may get it as they typically don't read comments)

.. cch::
  :code_path: warning_fallthrough_comment.cpp
  :color_path: warning_fallthrough_comment.color

See https://stackoverflow.com/a/45137452/4818802 for more information.

- C++17 fallthrough attribute used in a single statement alone in a place where you would normally put :cch:`break`:

.. cch::
  :code_path: warning_fallthrough_attribute.cpp
  :color_path: warning_fallthrough_attribute.color

If you have a situation where multiple cases are next to each other (without any code between them, like in the :cch:`break` example) then a fallthrough without any comment/attribute between them is fine:

.. cch::
  :code_path: case_adjacent.cpp
  :color_path: case_adjacent.color

Extra statement
###############

Just like with :cch:`if`, since C++17 it's possible to place an additional statement in :cch:`switch` to create objects with limited scope:

.. cch::
  :code_path: extra_statement.cpp
  :color_path: extra_statement.color

Trivia
######

Because :cch:`switch` has surprisingly permissive rules in regards to mixing it with other control flow statements, it's possible to cross it with a loop to create a `Duff's device <https://en.wikipedia.org/wiki/Duff%27s_device>`_.

You might understand the article better after few next lessons. Anyway, this trick for a long time is not used in production code because its primary purpose (loop unrolling optimization) is already done by compilers.

Summary
#######

Switch comes from C and features a quite unique behaviour - instead of having positive/negative branches it features execution start and stop, based on a set of possible jumps from a single source of comparisons.

- all cases must use a constant expression
- there can be a default case
- you can only test for equality

Because of these, switch in C++ is used mostly as an alternative, shorter version of if-else blocks, most often for *enumeration types*. The possibility of accidental fallthrough can be a good source of bugs but most compilers warn if any case has no break. If a fallthrough is intentional, it should be stated explicitly.

Exercise
########

Take the pseudo-calculator from the previous lesson and replace :cch:`if` statement(s) with :cch:`switch` where possible.

.. details::
    :summary: Hint

    :cch:`switch` should be used for operation selection.

----

.. [1] Generally, because in most situations it's not allowed. See `goto documentation <https://en.cppreference.com/w/cpp/language/goto>`_ for details over what transfer of control can jump.
