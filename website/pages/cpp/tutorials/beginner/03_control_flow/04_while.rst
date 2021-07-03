.. title: 04 - while
.. slug: 04_while
.. description: while loops in C++
.. author: Xeverous

The second most used type of control flow instructions are loops.

.. admonition:: definition
    :class: definition

    A loop is a repetitive execution of one (or more) statements as long as certain condition is satisfied.

While loop
##########

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        std::cout << "Enter a number: ";
        int x = 0;
        std::cin >> x;

        if (x == 0)
        {
            std::cout << "You entered zero.\n";
        }
        else
        {
            while (x % 2 == 0)
            {
                std::cout << "dividing " << x << "\n";
                x /= 2; // equivalent to x = x / 2
            }

            std::cout << "The final, odd value is " << x << ".\n";
        }
    }

Before each iteration, the condition is evaluated. If it's :cch:`false` the loop ends and execution continues after the loop's body. In worst case (when first condition evaluation returns :cch:`false`) the loop never runs.

As with :cch:`if`, if there is only a single statement braces can be skipped.

Test this program with big, even numbers like 1024 and any odd number.

    What happens when the condition is always :cch:`true`?

Well, then the loop never stops. Such programs (from user's perspective) will freeze and become unresponsive. It's programmer's responsibility to ensure that any loop always stops at some point.

Do-while loop
#############

An alternative loop is formed using :cch:`do` and :cch:`while` keywords. The only difference is that the condition is checked **after** the loop body, which means that it's guaranteed to execute at least once.

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x = 0;
        do
        {
            std::cout << "Enter a non-negative number: ";
            std::cin >> x;
        } while (x < 0);
        //             ^ spot the semicolon
    }

.. admonition:: note
    :class: note

    Do-while loop ends with a semicolon (``;``).

Breaking a loop
###############

It's possible to :cch:`break` a loop, exiting it prematurely. The following program is equivalent to the previous one:

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x = 0;
        while (true)
        {
            std::cout << "Enter a non-negative number: ";
            std::cin >> x;

            if (x >= 0)
                break;
        }
    }

Many would say this version has better code as do-while loops are known for their low readability. If you can, try to refactor do-while loops to other loops.

Advancing a loop
################

.. TODO

Recommendation
##############

In practice, do-while loops are rarely used. In almost all situations the condition needs to be checked before execution.

Exercise
########

.. TODO guessing game when? It requires random numbers.

Write a program that checks `Collatz Conjecture <https://en.wikipedia.org/wiki/Collatz_conjecture>`_ (AKA the 3n + 1 problem):

- input a positive number
- while the number is not 1:

  - if it's even, divide it by 2
  - if it's odd, multiply it by 3 and add 1
  - print new value

For all positive numbers, the program should eventually terminate at 1 (otherwise it loops 1, 4, 2, 1, 4, 2, ...). At least that's what the conjecture states - **it's still an unsolved problem in mathematics**.

Example sequences to test:

- for 7: 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
- for 15: 46, 23, 70, 35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1

Even though huge numbers have been tested, no proof or pattern has been found that would guuarantee that every number reaches 1. If negative numbers are allowed, there are 3 extra known loops:

- -1, -2, -1
- -5, -14, -7, -20, -10, -5
- -17, -50, -25, -74, -37, -110, -55, -164, -82, -41, -122, -61, -182, -91, -272, -136, -68, -34, -17

If you want to learn more about this problem - watch `Numberphile's videos about it <https://www.youtube.com/results?search_query=numberphile+collatz+conjecture>`_.
