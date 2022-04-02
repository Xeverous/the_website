.. title: 03 - access specifiers
.. slug: index
.. description: introduction to encapsulation
.. author: Xeverous

When browsing settings on an online account or government documents, you can sometimes find that some data is marked as **public** (everyone can see it) or as **private** (only you can see it). We limit access to certain data in order to prevent unauthorized people from accessing data they shouldn't need. An analogical mechanism exists in object-oriented programming: we limit access to class members in order to prevent unwanted code to accidentally interact (in a bad way) with class invariants.

There are 3 keywords which affect class member access:

- :cch:`public`
- :cch:`protected`
- :cch:`private`

:cch:`public` is something you already know. It places no restrictions and is the default access when a class is defined using the :cch:`struct` keyword.

The remaining 2 place certain restrictions:

- :cch:`private` - only class member functions can use affected member
- :cch:`protected` - only class and *derived class* member functions can use affected member (slightly less restrictive than :cch:`private`)

Derived classes will be explained in a later chapter. Up to that point, there will be no visible difference between :cch:`private` and :cch:`protected`. Right now we will only focus on public vs private access.

Encapsulation
#############

We have modified the class:

- member variables are now private
- added a public function to set the values
- added reasonable default initializers (simplest form of a fraction representing 0)

.. cch::
    :code_path: encapsulation.cpp
    :color_path: encapsulation.color

The change has important consequences:

- Because direct access to member variables is no longer possible and must be done through a public function, the function can verify that passed data is correct. This shields objects from breaking invariants.
- Because the type contains non-public data members, it has stopped being an *aggregate*. This means that aggregate initialization (which uses ``{}``) is no longer possible. This is only a temporary problem - in few lessons you will see multiple ways how to initialize class objects.

At this point we can say we have created a type that has:

- an interface (public members) - a way to interact with the object from the outside
- an implementation (private members) - details how stuff is done, only to be accessed (indirectly) through the interface

...and this is the key to write code that cooperates with other projects. If you use someone else's code (e.g. from a library project) methods can be changed (e.g. library update) and code that uses them will also change its behaviour. In this regard methods save us from rewriting the program - all of your code automatically gets indirect update when a library's method implementation is changed. You have already wrote code that relies on it - the C++ standard library also gets updates on its specification and compiler vendors continuously work on improving the code inside.

.. admonition:: note
    :class: note

    Library project interfaces are commonly referred to as **API** (application programming interface). We can say that the website `cppreference <https://en.cppreference.com/>`_ documents C++ standard library API.

.. admonition:: tip
    :class: tip

    Generally, for a class that has invariants:

    - All member variables should be :cch:`private`.
    - Functions which are a part of the class interface should be :cch:`public`.
    - Functions which are a part of the implementation (often helper functions to be used inside public functions) should be :cch:`protected` or :cch:`private`.

In the case of a class representing a fraction, there was no need for private functions but once your classes get bigger, you might need to split/extract some code from public functions to simplify or deduplicate their code. Protected/private functions in such case should be used - they are a detail how interface is realized so they should not be a part of the (public) interface.

    What if there are invariants but only between certain fields? What if other fields have no invariants? Should first group of fields be private and the second group be public?

Such situation indicates that the class has been badly designed. Very likely, fields with invariants should form a class on their own, and the remaining fields should be added in another class definition through *composition* or *inheritance*.

When in doubt, a good default is to make more smaller classes. Such code is more reusable, modular and testable.

More analogy
############

Kitchen (and other household) devices are pretty good examples - they are relatively simple to use but hide complicated mechanisms inside.

.. list-table::
   :header-rows: 1

   * - device
     - invariant
     - private data
     - private functions
     - public functions (interface)
   * - microwave
     - no microwaves emitted when opened
     - current power, rotating speed
     - rotate plate, switch light, emit microwaves
     - switch on/off, set time, set power, open, close
   * - fridge
     - light is off when closed
     - compressor state
     - switch light, compressing power
     - open, close, input item, take item
   * - dishwasher
     - no water when opened
     - available water, current program stage
     - enable water pump, rotate nozzles
     - switch on/off, set program, open, close

Many devices of the same purpose will share the same interface but may be constructed differently. Another great example of an interface is a power socket. Different devices can access the power from the same interface.

Of course you might have a device that does not match the table above - sometimes it can be quite hard to determine what should be a part of (public) interface and what should be controlled internally.

Making **and justifying** decisions is one of programming skills that come with time. Many of OOP design decisions are not always trivial. Some problems take a lot of attempts and experiments to achieve satisfying solution. Remember that **the best way to learn programming is by writing code**. The more problems you encounter and solve, the better.

Other kinds of members
######################

Class members are not only variables and functions. Classes can also contain *member types*. These can be type aliases or other classes, defined within class body (for nested classes some restrictions apply though).

.. TOEXAMPLE mb something with member container_type?

Order of sections
#################

There is no required order of sections within a class. You can also repeat access specifier keywords - this is sometimes required if definitions of certain members need at least declarations of other members.

The traditional convention is to list members in this order: :cch:`public`, :cch:`protected`, :cch:`private` though I have seen some people (most notably Howard Hinant) recommending the reverse order. The argument is that for a typical class there are far less private members than public members and seeing private members at first would help understand how the class works and what it represents.

Core Guidelines `recommend traditional order in NL.16 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rl-order>`_ though they state *This is a recommendation for when you have no constraints or better ideas.*.
