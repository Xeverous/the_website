.. title: 03 - switch
.. slug: 03_switch
.. description: switch statements in C++
.. author: Xeverous

:cch:`switch` is also a form of conditional statement but it has different rules regarding execution - it allows a *fallthrough* control flow.

The **fallthrough** behavior comes from the fact that unlike :cch:`if` or :cch:`else`, a :cch:`switch` statement can execute multiple sections of code based on a single condition. There is no positive/negative branch. There are only places where execution starts and stops.

Rules
#####

The syntax is slightly different from :cch:`if`:

- :cch:`if` requires a value of type :cch:`bool` (or something *contextually convertible* to it), :cch:`switch` requires a value of integral or enumeration type (or something *contextually convertible* to it).
- Each :cch:`case` must use a *constant expression* (it must be computable at compile time).

Then, the expression in :cch:`switch` is evaluated once and compared for equality with cases in order of their appearance. It's not possible to make a different comparison (e.g. ``!=``).

.. TODO when constexpr?

Compile the following program and test how it behaves for different numbers:

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        std::cout << "Enter a number: ";
        int x = 0;
        std::cin >> x;

        switch (x)
        {
            case 3:
                std::cout << "you entered 3 or a higher number\n";
            case 2:
                std::cout << "you entered 2 or a higher number\n";
            case 1:
                std::cout << "you entered 1 or a higher number\n";
            case 0:
                std::cout << "you entered 0 or a higher number\n";
        }
    }

The **execution starts on first matching case and then goes through all subsequent cases (fallthrough), without further testing for a match**. If you don't get it, try reordering cases so that values are no longer in descending order.

Said differently, a :cch:`switch` statement has no branches but a point where execution starts.

    Why case values have to be constant expressions?

Unlike if-else, :cch:`switch` (at least when it was introduced in C) was not only supposed to be a shorter version of if-else but also feature a specific optimization: jump table. The goal was to have only one condition which result affects a jump instruction, which then computes new memory address based on a table build up from constant expressions.

Today, compilers also perform this optimization on if-else blocks if possible.

    What does it mean that the expression inside :cch:`switch` is evaluated once?

It means that any code there will be run once. For example, :cch:`switch(func())` will call the function only once, no matter how many cases are present. This is contrary to loops, where a condition is evaluated once per iteration.

Breaks
######

:cch:`break` is where the execution stops. In other words, it disables fallthrough.

.. TOCOLOR

.. code::

    // for 1, prints "12345"
    // for 2, prints "2345"
    // for 3, prints "345"
    // for 4 and 5, prints "45"
    // for 6, prints "6"
    // for anything else, does nothing
    switch (x)
    {
        case 1:
            std::cout << "1";
        case 2:
            std::cout << "2";
        case 3:
            std::cout << "3";
        case 4:
        case 5:
            std::cout << "45";
            break;
        case 6:
            std::cout << "6";
    }

If you add a :cch:`break` to every statement then :cch:`switch` behaves the same way as if-else blocks:

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        std::cout << "Enter a number: ";
        int x = 0;
        std::cin >> x;

        switch (x)
        {
            case 3:
                std::cout << "you entered 3\n";
                break;
            case 2:
                std::cout << "you entered 2\n";
                break;
            case 1:
                std::cout << "you entered 1\n";
                break;
            case 0:
                std::cout << "you entered 0\n";
                break;
        }
    }

Default case
############

You can add a :cch:`default` case which will be executed if no other cases were matched (or if previous case allowed *fallthrough*). This is equivalent to the last :cch:`else` (with no condition) in an if-else sequence.

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        std::cout << "enter a number: ";
        int x;
        std::cin >> x;

        switch (x)
        {
            case 3:
                std::cout << "you entered 3\n";
                break;
            case 2:
                std::cout << "you entered 2\n";
                break;
            case 1:
                std::cout << "you entered 1\n";
                break;
            case 0:
                std::cout << "you entered 0\n";
                break;
            default:
                std::cout << "you entered something different\n";
                break;
        }
    }

Scope
#####

While :cch:`if` always introdues an inner scope the :cch:`switch` does not - all cases share the same scope. This can sometimes create problems because generally\ [1]_ transfer of control is not permitted to enter the scope of a variable.

.. TOCOLOR

.. code::

    switch (x)
    {
        case 1:
            int y = 0; // initialization
            std::cout << y << '\n';
            break;
        default:
            // compilation error: jump to default would
            // enter the scope of y without initializing it
            std::cout << "default\n";
            break;
    }

To fix it simply introduce a scope:

.. TOCOLOR

.. code::

    switch (x)
    {
        case 1:
        {
            int y = 0; // initialization
            std::cout << y << '\n';
            break;
        } // y dies here
        default: // braces not necessary here but use them for consistency
        {
            std::cout << "default\n";
            break;
        }
    }

Warning: no default
###################

Many compilers issue a warning when a :cch:`switch` has no :cch:`default` case (for a good reason) - usually it means that the programmer forgot to write code for when no :cch:`case` matches. If you actually want to do nothing if no case is matched, simply add a :cch:`default` case immediately terminated by a :cch:`break`:

.. TOCOLOR

.. code::

    switch (x)
    {
        case 0:
            // ...

        // more cases...

        // this is how you silence the warning
        // and explicitly state that nothing should be done
        default:
            break;
    }

.. admonition:: tip
    :class: tip

    It's much better to explicitly state that you want to do nothing than make others reading your code question if you have forgot to handle such situation.

Warning: fallthrough
####################

In practice, fallthrough is hardly ever desirable. Even if it is, people instinctively use a separate :cch:`if` earlier in the code which makes :cch:`switch` unneeded. For these reasons, compilers warn when fallthrough can happen - in almost all cases it's unintended.

If you really want to do fallthrough (and silence the warning), there are 2 ways:

- "fallthrough" comment (not all compilers may get it as they typically don't read comments)

.. TOCOLOR

.. code::

    case 3:
        std::cout << "you entered 3 or a higher number\n";
        // fallthrough
    case 2:
        std::cout << "you entered 2 or a higher number\n";
        // fallthrough
    case 1:
        std::cout << "you entered 1 or a higher number\n";
        // fallthrough
    case 0:
        std::cout << "you entered 0 or a higher number\n";
        break;
    default:
        std::cout << "you entered a different number\n";
        break;

See https://stackoverflow.com/a/45137452/4818802 for more information.

- C++17 fallthrough attribute used in a single statement alone in a place where you would normally put :cch:`break`:

.. TOCOLOR

.. code::

    case 3:
        std::cout << "you entered 3 or a higher number\n";
        [[fallthrough]];
    case 2:
        std::cout << "you entered 2 or a higher number\n";
        [[fallthrough]];
    case 1:
        std::cout << "you entered 1 or a higher number\n";
        [[fallthrough]];
    case 0:
        std::cout << "you entered 0 or a higher number\n";
        break;
    default:
        std::cout << "you entered a different number\n";
        break;

If you have a situation where multiple cases are next to each other (without any code between them, like in the :cch:`break` example) then a fallthrough without any comment/attribute between them is fine:

.. TOCOLOR

.. code::

    // this is fine, compilers will not warn on this
    case 6:
    case 5:
    case 4:
    case 3:
    case 2:
    case 1:
        std::cout << "you entered " << x << "\n";
        break;
    default:
        std::cout << "invalid number\n";
        break;

Extra statement
###############

Just like with :cch:`if`, since C++17 it's possible to place an additional statement in :cch:`switch` to create objects with limited scope:

.. TOCOLOR

.. code::

    switch (int x = user_input(); x)
    {
        // ...
    }

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
