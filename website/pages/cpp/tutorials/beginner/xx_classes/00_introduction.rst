.. title: 00 - introduction
.. slug: 00_introduction
.. description: introduction to object-oriented programming
.. author: Xeverous

So far you have used built-in types and some of the uder-defined types provided in the C++ standard library. You have also learned how to create simplest user-defined types - enumerations. This chapter is dedicated towards a much more powerful type mechanism - classes, which are a very significant building block in OOP (object-oriented programming). OOP is all about representing real-world things as *objects* that can have certain similarities and (potentially shared) behaviors.

C++ is a multi-paradigm language. OOP is one of it's bigger features, but it's not required - in contrast, some languages force OO style of programming and their "hello world"s can not be written without creating a class. This conflicts with C++ philosophy and the goal that you don't pay for what you don't use. Most of the C++ standard library uses generic programming rather than OOP. Some of the most powerful design techniques combine aspects of traditional object-oriented programming, generic programming, functional programming, and some traditional imperative techniques [1]_.

This lesson is a more philosophical than others but further ones in this chapter showcase a lot of new code. It's important to not only understand *how*, but also *why*. You can perfectly memorize all OOP rules - most of them are very intuitive; write any program that satisfies given requirements but whether the code will be a good code is a very different topic. This is the place where you will realize you have almost limitless ways to complete a task and the true art of programming is in making choices what features to use. Common combinations of specific features to solve popular problems are known as **design patterns**.

So what exactly is a class? In simple terms, it's a box of closely related variables (called **fields**) which are intended to be used together. Such box can have own class-specific functions (called **methods**) which are specifically designed to work on objects of the class type. These together with other class-specific features tie data with operations to create very reusable building blocks for bigger programs.

Classes can improve code readability and offer modular design. They also feature a slightly different syntax:

.. code::

    set_text(button, "hello"); // structural
    button.set_text("hello");  // object-oriented

Isn't the second line more intuitive?

- The structural approach uses a global function which takes (a reference to) a button and the text to set.
- The OO approach uses a class-specific function which takes only the text to set. Method is invoked on the button object - note how ``.`` has to be used to access it. This is because methods are tied to classes and therefore have to be invoked on objects of certain types.

Related terms
#############

OOP is related to few important terms:

- **abstraction** - *selective ignorance*. We can hide (abstract away) uninteresting things and focus on what is important.
- **encapsulation** - classes group related variables and functions and can constrain their usage through access specifiers. This leverages type safety and helps with modular design.
- **inheritance** - classes can be build as extentions to other classes. Massive code reuse.
- **polymorphism** - classes can provide interfaces - uniform way of treating objects on the outside with custom behavior on the inside. Ability of *related* classes to behave differently while sharing common interface.

.. admonition:: note
    :class: note

    Classes do not exist in C.

Defining classes
################

.. admonition:: note
    :class: note

    For historical reasons, classes in C++ were originally defined using :cch:`struct` keyword. Later :cch:`class` keyword was introduced. **The only difference between keywords** :cch:`struct` **and** :cch:`class` **are default access specifiers for member access and inheritance.**

..

    Does it mean that structures defined in previous lessons were technically classes?

Yes - C++ does not differentiate classes and structures. It's one thing that can be defined using 2 keywords - only default access is different. More on access in later lessons.

.. admonition:: tip
    :class: tip

    By convention, use :cch:`class` whenever you want something more than just a box of variables. :cch:`struct` should only be used when there are no constraints/conditions between fields. If in doubt, use :cch:`class`.

So far we relied on implicit :cch:`public` access default in structures. Because of different defaults in classes, in order to have the same behavior as with :cch:`struct`, we need to specify the access as :cch:`public`. **In the code below all definitions are equivalent.**

.. TOCOLOR

.. code::

    struct point
    {
    // (implicitly public)
        int x;
        int y;
    };

    struct point
    {
    public:
        int x;
        int y;
    };

    class point
    {
    public:
        int x;
        int y;
    };

----

.. [1] Direction for ISO C++, Long-term aims, http://wg21.link/p2000
