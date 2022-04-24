.. title: 01 - inheritance
.. slug: index
.. description: introduction to inheritance
.. author: Xeverous

You can create classes which contain objects of different types, possibly different classes. This is known as **composition**. You can also create classes which are an extension of existing classes. This is known as **inheritance**.

Example
#######

Suppose a shop which sells car parts. I will showcase 2 ways to implement similar code, both will use this code fragment:

.. cch::
    :code_path: base_fragment.cpp
    :color_path: base_fragment.color

An example product written using *composition*:

.. cch::
    :code_path: composition.cpp
    :color_path: composition.color

The same product written using *inheritance*:

.. cch::
    :code_path: inheritance.cpp
    :color_path: inheritance.color

In the second example, the :cch:`tyre$$$type` class has not been defined as containing a :cch:`product$$$type`, but **as an extensions of it**.

It has the following effects:

- :cch:`tyre$$$type` gets (*inherits*) all of :cch:`product$$$type` members. You can call :cch:`product$$$type` member functions on objects of type :cch:`tyre$$$type`.
- Objects of type :cch:`tyre$$$type` are *implicitly convertible* to :cch:`product$$$type`.
- When constructing :cch:`tyre$$$type`, in *member init list*, type name (:cch:`product$$$type`) is written instead of member name.

Code which uses :cch:`tyre$$$type` will be slightly different depending on the implementation:

.. cch::
    :code_path: usage.cpp
    :color_path: usage.color

Untill we move to more advanced features available through *inheritance*, you may have a feeling that both *composition* and *inheritance* can achieve the same thing, they just produce slightly different code... and you would be right.

.. admonition:: tip
  :class: tip

  If possible, favor *composition* over *inheritance*.

Inheritance will start to make sense once you reach further topics described in this chapter, specifically *virtual functions*. If such features are not being used, more often than not writing inheritance-based code is a mistake. Practice has shown that composition results in simpler code that is easier to maintain and has less bugs, thus **you should prefer composition when there is no need for inheritance-specific features**.

Terminology
###########

When speaking about inheritance:

- the type that is used as a base is called *base type*
- the type that *inherits* from base is called *derived type*

We can say that:

- :cch:`tyre$$$type` is derived from :cch:`product$$$type`
- :cch:`product$$$type` is a base of :cch:`tyre$$$type`

Other popular set of names is *parent* and *child*:

- :cch:`tyre$$$type` is a child of :cch:`product$$$type`
- :cch:`product$$$type` is a parent of :cch:`tyre$$$type`

.. admonition:: note
  :class: note

  Just like composition can nest objects within objects, inheritance can:

  - be used to define classes that inherit from already derived classes (multiple layers of inheritance)
  - be applied multiple times for the same class (*multiple inheritance* - a situation when a class has multiple parents)

A **direct base** is a class that is an immediate base type of the given class.

Another set of terms specifies how an object is seen:

- A **static type** is a type of the object that is visible during compilation of the program.
- A **dynamic type** is the real type of the object during runtime, which might be identical to the *static type* or be a type derived from it.

Inside the function :cch:`calculate_bargain_percent$$$func` which was called in the expression :cch:`calculate_bargain_percent(t)$$$func(var_local)`:

- The *static type* of the argument is :cch:`product$$$type` - that's what the function sees.
- The *dynamic type* of the argument is :cch:`tyre$$$type` - actual object given is of this type.

How it works? How can a function operate on an object which type is derived from the argument type? Strictly technically it's *implementation-defined* but to illustrate typical compiler implementation:

- An object of base type occupies ``B`` bytes in memory.
- An object of derived type occupies ``D`` bytes in memory (typically ``D > B`` but ``D == B`` if derived type has no extra *non-static data members*).
- A function which references base type only operates on first ``B`` bytes of the object.
- The remaining bytes (``D - B`` bytes exactly) are not accessed by the function - it doesn't know if the object if of derived type. There might be actually multiple derived types (with sizes ``D1``, ``D2``, ``D3``, ...) where after first ``B`` bytes, each has different data further in memory.

The implicit convertion mentioned earlier (*upcast* - the convertion from derived type to base type) doesn't actually do anything in the machine code (unless *virtual inheritance* is used) - it's purely a language abstraction. For any ``D1``, ``D2``, ``D3`` bytes of derived types the fitst ``B`` bytes will be the same and represent the base type object.

Speaking about *dynamic types* only makes sense when objects are referred through pointers or references. Otherwise dynamic type can not be different from the *static type*.

Construction
############

Objects are initializated by calling constructors of base types first, then of members. Apart from initialization of members and *delegating constructors*, *member initializer list* can also call constructors of *direct base* classes (they have to be constructed somehow after all). If no initializers are given, default constructor is assumed.

This example doesn't use calls to base type constructors but the order of prints should let you understand in what order objects are being initialized:

.. cch::
    :code_path: construction.cpp
    :color_path: construction.color

Output:

.. code::

    X::X()
    A::A()
    B::B()
    X::X()
    Y::Y()
    Z::Z()
    C::C()

:cch:`protected`
################

You already know that :cch:`public` sets no restrictions and :cch:`private` only gives the access to code within the class.

:cch:`protected` works like :cch:`private` but additionally grants access to derived classes.

Access when deriving
####################

You very likely noticed that inheritance wasn't written as :cch:`class tyre: product$$$keyword type: type` but as :cch:`class tyre: public product$$$keyword type: keyword type`. Actually, the first one is valid syntax too - it just uses default access specifiers. Just like for members with no explicitly specified access:

.. admonition:: note
  :class: note

  - The default inheritance for :cch:`struct` is :cch:`public`.
  - The default inheritance for :cch:`class` is :cch:`private` (rarely useful).

.. TOINCLUDE cheatsheets - inheritance access

.. list-table::
    :header-rows: 1

    * - access in base
      - derived as public
      - derived as protected
      - derived as private
    * - public
      - public
      - protected
      - private
    * - protected
      - protected
      - protected
      - private
    * - private
      - (no access)
      - (no access)
      - (no access)

..

    Does it mean that inside :cch:`tyre$$$type` functions, there is no access to :cch:`private` members of :cch:`product$$$type`?

Yes. And that's a good thing. Derived types should not mess with their base type :cch:`private` data. A class is supposed to encapsulate specific behavior and member functions are supposed to preserve class invariants. Practice has shown that if derived types can modify base type data members there is a high chance of creating a bug by breaking invariants.

The `open-closed principle <https://en.wikipedia.org/wiki/Open–closed_principle>`_ states that classes should be open for extension, but closed for modification. Thus, the general recommendation is:

- data members should be :cch:`private`
- functions intended to be used everywhere should be :cch:`public`
- functions intended to be used in current class and its derived classes should be :cch:`protected`
- functions intended to be used only in other functions of the current class should be :cch:`private`
- inheritance should use :cch:`public` access

If data has invariants (one of primary purposes of classes is to preserve invariants), :cch:`private` enforces that only the class that manages this data has access to it. If a derived class wants to modify data of its parents, it should do so through parent's :cch:`public` or :cch:`protected` functions.

It's worth mentioning that non-public inheritance is a C++-specific feature (at least I haven't seen another language that supported it). Other languages do not have the concept of changing access level in derived types, they do not have a syntax that supports access specifier in inheritance and always work as if the type was derived as :cch:`public`. Non-public inheritance is not typical OOP practice, it's a niche within C++ for some implementation tricks (many which are used in standard library implementations).

Classes which are derived in non-public way disallow convertions to their non-public bases for code outside the class. This effectively prevents any outside code in treating the type as if it was a base, making inheritance act as a hidden implementation detail, usually only for the purpose of code reuse inside the class. Any external code can only treat the class as if it had no such parent. Why composition is not used in such cases? It could be, but specific :cch:`template` patterns in C++ (e.g. *policy-based design*) are easier and more optimal (*empty base optimization*) to write this way.

.. admonition:: tip
  :class: tip

  When implementing typical OO code (not non-OO implementation tricks for something else) always use :cch:`public` inheritance.

Shapes example
##############

A very popular inheritance example uses shapes, which looks like this:

- triangle is a shape
- quadrangle is a shape
- rectangle is a quadrangle
- square is a rectangle

Intuitively, shapes seem to be a great example of an **is-a** relationship. The problem is that this example suggests a class hierarchy which violates LSP (`Liskov substitution principle <https://en.wikipedia.org/wiki/Liskov_substitution_principle>`_). LSP states that if something can be done with one type, it should also be possible with its derived types. Derived types are supposed to be extensions, not limitations.

- in mathematics, more derived types have stronger invariants (rectangle has 2 parallel sides of equal length, square has 4 sides of equal length)
- in programming, more derived types are expected to:

  - not have stronger preconditions
  - not have weaker postconditions

Apart from violating LSP, there are representation problems too:

- If rectangle is represented as 2 variables describing side lengths, a square would make no sense with 2 variables
- If rectangle is represented as 4 points and functions which allow to modify them, a square would not work with these functions because it has stronger requirements.

..

    So, should it be reverse? A rectangle inheriting square?

No. **OOP is simply not feasible to be used for this problem**. Another important detail is that the square-rectangle problem is very abstract - it encourages thinking in terms of mathematical logic instead of practical approaches like "which code is reused, which code is extended". In practice, code is used to implement specific behavior so **first, you should look at the problem and find out any patterns/invariants within it before deciding on any particular abstraction**. Inheritance makes no sense if LSP can not be satisfied. OOP is very popular, but it's not panacea and is not an appropriate solution to every abstraction problem.

- If it's some tile-based game or simulation, there is no need to create different classes for different shapes - everything on the board/map can be treated as rectangle. Sometimes there may be squares, but if there is a need for any extra logic it will be implemented alongside rectangle-handling code, not as a derived class.
- If it's some 2D/3D graphics rendering code, if there will be any hierarchy it will be that all concrete shapes inherit "base shape" class. Each shape will have its own specific function that implements particular rendering algorithm. The only extension would be that all shapes implement rendering.

The square-rectangle problem (AKA circle-ellipse) has also been described in on https://en.wikipedia.org/wiki/Circle-ellipse_problem.

Summary
#######

This lesson is more philosophical than others in this chapter, similarly to the first lesson in the classes chapter. It doesn't present a lot of compilable code - it's more important that you understand the concept and the good practices that come with it. You can perfectly memorize all language rules and still write compiling, working code that will be just bad: hard to modify/maintain, unclear and bug-prone.

In the classes chapter, you learned about *single responsibility principle* - a class should represent exactly one thing (and take care to preserve its invariants). That's **S** in `SOLID <https://en.wikipedia.org/wiki/SOLID>`_.

In this lesson, 2 additional principles were mentioned:

- **O** - the open-closed principle
- **L** - Liskov substitution principle (LSP)

The last 2 will be explained later. LSP will become even more significant once you read about *virtual functions*.

FAQ
###

    Upcasts are allowed as implicit convertions. How about downcasts?

Downcasts must be explicit and there are semantic differences between :cch:`static_cast` and :cch:`dynamic_cast`. Explained in a later lesson in this chapter.

    Can a class inherit from and contain a member of the same type?

Yes, but it doesn't make much sense - what would you do with 2 sets of the same functionality, each with slightly different syntax? You should do one of these or none if OO style is not appropriate for the given problem. Typically by looking at the definition of a class it can be said whether it's supposed to be contained (as a member) or inherited from - by default we can assume containment ("prefer composition over inheritance") and decide on inheritance by noticing inheritance-specific features such as *virtual functions*. Every class can be used as a member but only specific kinds of classes makes sense to inherit from.

    Can a class inherit from another multiple times?

Yes, but not on the same inheritance level. It's not so rare but usually accidental, which creates the *diamond problem*. Explained in a later lesson in this chapter.
