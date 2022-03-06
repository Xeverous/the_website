.. title: 05 - objects
.. slug: 05_objects
.. description: making objects in C++
.. author: Xeverous

You already know basic types in C++. Time to create some *objects*.

What is an object?
##################

It's hard to give a simple and consise definition of an object that doesn't just go by listing every C++ language rule attached to it, so to put it simply: **objects are data in memory**.

Every object has:

- *lifetime* (when associated memory can be used)
- type (how the bit pattern should be interpreted)
- value (actual bit pattern in memory)
- (optionally) a name (identifier)
- some memory-related properties (address, size, alignment, storage duration) that won't be interesting for now

Name is optional because:

- In some cases temporary (unnamed) objects may be created as a part of evaluation of expressions - e.g. in :cch:`2 * 3 + 4$$$num * num + num` an unnamed integer object with value :cch:`6` may temporarily appear in memory.
- In some cases objects can be referred using indirect mechanisms such as pointers and references. This is especially true for any data that has variable size (e.g. an array).

Don't think that an *object* (some data in memory with certain properties) means the same as a *variable* (named modifiable entity in code):

- When using indirect mechanisms such as references and pointers, it's possible to have 2 variables (e.g. 2 references) that refer to the same object in memory.
- When using variable-size objects such as arrays, it's possible to have multiple objects that are accessed through the same variable.

Of couse we are still pretty far from indirect mechanisms, all of the code now will have 1:1 variable-object relation.

If you are curious for the formal difference:

.. admonition:: definition
    :class: definition

    A *variable* is an *object* or a *reference* that is not a *non-static data member*, that is introduced by a *declaration*.

Creating objects
################

Before using an object, you must first specify what type it will be.

.. TOCOLOR

.. code::

    x;             // error: it is unknown what x actually is
    int x;         // ok: definition of an object named "x" of type int
    long double y; // ok: definition of an object named "y" of type long double

At this point, the compiler will determine any other properties such as memory location automatically.

It's possible to define multiple objects at once:

.. code::

    int x, y, z; // 3 objects of type int

...but **such practice is very discouraged**. For historical reasons (mostly backwards compatibility), C++ adopted C grammar which while generally brilliant, has some peculiarities and most of them lie in *decl-specifier-seq* subgrammar, which is used for declarations. I don't really want to list all possible corner cases (there can be infinitely many of them as the grammar can be nested), I just want to point out that thinking of object declaration syntax as "type followed by name" is fundamentally wrong with how C/C++ grammar works and for this reason:

.. admonition:: tip
    :class: tip

    Declare only 1 entity per statement.

This is a very common C++ teaching mistake - please point it out by giving link to this article TODO. While I understand the need for mental shortcuts, "type followed by name" is only trapping beginners in incorrect thinking. We wish it worked this way, but it doesn't.

To further prove the argument, take a look at this:

.. code::

    // x has type int*[2]
    // y has type int
    // z has type int*
    // p has type int (*)(float)
    int* x[2], y, *z, (*p)(float);

In this specific example, only :cch:`int` is "picked up" for every object and any other type modifiers seem to be in random places. No one wants to deal with such unintuitive rules - they are only maintained for backwards compatibilty.

.. admonition:: tip
    :class: tip

    Always declare each variable in a separate statement. Never declare mutliple variables in one.

..

    Can't these syntax rules be changed?

C++ is a very history-rich language (40+ years) and it also takes backwards compatibility very seriously. C++ inherited a lot from C, including some of its grammar design flaws. Still, it wouldn't be in a place it is today if the language did not appear as an alternative to then very fast growing C. Many of past problems did get "fixed" in C++11 **without breaking backwards compatibility** by adding more alternative subgrammars. This of course spawned a lot of corner cases so if you want some laugh, watch the 7min talk `CppCon 2018: Timur Doumler "Can I has grammar?" <https://www.youtube.com/watch?v=tsG95Y-C14k>`_.

Assignment
##########

After an object has been created, we can start using it. One of the simplest operations you can perform is assignment:

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x;
        x = 1;
        std::cout << x << "\n";
        x = 2;
        std::cout << x << "\n";
    }

You can observe that statements are executed from top to bottom and :cch:`x`'s value is changed.

Initialization
##############

If an object definition is combined with giving it a value, it's called **initialization**.

.. TOCOLOR

.. code::

    int x = 1;

It looks just like a shortcut version of previous code (AKA *syntax sugar*) but **initialization is fundamentally different from assignment**:

- an object can be assigned any time after its creation
- initialization can happen only once: when the object is created

Right now there is no visible difference but it will be very important later. Even though both assignment and initialization use ``=``, they are technically very different operations.

.. admonition:: tip
    :class: tip

    Always initialize variables upon their creation.

There is nothing wrong in assignment, however the first ever value than an object will hold should be given through initialization. Reasoning is pretty simple:

- Initialization offers more than the assignment:

  - Sometimes only initialization will be possible - such is the case of :cch:`const` objects. They can be initialized, but never assigned.
  - Sometimes initialization will be more optimal than creation + assignment.
  - Sometimes initialization will be required.

- If you create an object, but can't give any value to initialize it with, you very likely don't need the object. In such case, the object creation should be postponed (done later in the code) to the moment it's actually needed.

..

    If initialization is so important, why objects aren't intialized automatically by the compiler?

In some programming languages (usually ones which operate on higher abstraction level) they actually are, but C++ (and its ancestor - C) have always fundamentally followed the rule that you don't pay for what you don't use and if something is not absolutely necessary, it shouldn't be done - at least automatically. The performance penalty of "dead writes" (e.g. initializing an object with some value but never reading it before future assignment) is getting lower, but it's still not zero and C++ doesn't like forcing things that are not required. A lot of people advocated for a reversed default though, where initialization would be opt-out, not opt-in as in vast majority of cases the programer wants to be warned about missed initialization and the need for optimizing to the point of removing single write instructions is very rare.

Other reasons include backwards compatibility and the inability to provide good defaults. For any numeric type, zero is a very good choice. For :cch:`bool` it's :cch:`false` because it is represented by bit 0. But for a lot of types there is no good default and their bit representation made full of 0s may have no valid interpretation.

Syntax
======

Initialization can be performed in multiple ways:

.. TOCOLOR

.. code::

    int x = 1;   // copy initialization
    int x(1);    // direct initialization
    int x{1};    // direct list initialization
    int x = {1}; // copy list initialization
    int x{};     // value initialization

Each of these has slightly different rules. There are even more than in the example, but they can not be used for built-in types like :cch:`int`.

For now, we will stick to copy initialization as ``=`` is definitely the easiest and most intuitive syntax to remember. We will come back to different ways of initialization once you gain more knowledge about the type system in C++.

Printing values
###############

Now you should be familiar with how to create objects and give them values. Time to learn how to print them.

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x = 1;
        int y = 2;
        std::cout << "x = " << x << "\n";
        std::cout << "y = " << y << "\n";
    }

Standard character output accepts many kinds of data and the input can contain arbitrary amount of expressions. These expressions are separated by ``<<``. ``\n`` is a special control character that denotes new line (AKA line break or line feed character). Since the first expression in the next statement is also text, we can actually combine 2 statements into 1:

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x = 1;
        int y = 2;
        std::cout << "x = " << x << "\ny = " << y << "\n";
    }

Sometimes you might also see :cch:`std::endl` (end-line) used instead of new line character:

.. TOCOLOR

.. code::

    #include <iostream>

    int main()
    {
        int x = 1;
        int y = 2;
        std::cout << "x = " << x << std::endl;
        std::cout << "y = " << y << std::endl;
    }

The output of this code is the same, however :cch:`std::endl` is not just a new line character. It does something more, something which shouldn't really be done explicitly - it flushes the buffer. Outputting any data to the operating system is a task which requires some extra work (very often system-specific). Buffering the output, while not necessary is very often done for performance reasons. C++ standard streams accumulate data as it is passed in and only output it in bulk when needed. The reason for this is that regardless of data size, communication with operating system is an expensive (in computation and/or time) operation so it should be avoided when possible.

C++ standard streams automatically flush the buffer when necessary, so you shouldn't really be concerned with what is happening underneath. Using :cch:`std::endl` forces it to flush the buffer more than necessary, which generally only slows down the whole program. If you see examples online which use :cch:`std::endl`, you can simply rewrite them to use new line character.

For now, this should be enough to let you output values of simple variables. Play with different types and values and observe the effect. In later lessons, you will learn about standard input (:cch:`std::cin`) and how to create first user-interactive programs that read text.

Exercise
########

Is the following code valid?

.. TOCOLOR

.. code::

    int x = 5;
    x = x * 2;
    std::cout << x;

.. details::
    :summary: Answer

    Yes. Assignments work by evaluating expression on the right before the result is stored in an object. There are no problems if the expression refers to the same object.

Is the following code valid?

.. TOCOLOR

.. code::

    int x = 2 * x;
    std::cout << x;

.. details::
    :summary: Answer

    Technically yes (this will compile) but contains undefined behavior. :cch:`x` here is used (on the right side) before it's initialized. It's not possible to correctly initialize an object with a value that depends on it.
