.. title: 08 - multiple inheritance
.. slug: index
.. description: interface inheritance vs implementation inheritance
.. author: Xeverous

Being able to inherit multiple times doesn't seem complicated. A class simply reuses code from multiple other classes. But practice has shown that multiple inheritance can be very easily overused and lead to strongly coupled, hard to maintain code.

Duplicate function name
#######################

In such case there is no problem although technically there are 2 chains of virtual functions here.

Overriding is not required in :cch:`derived$$$type` but if not done then calls through :cch:`derived$$$type` are ambiguous and thus *ill-formed*. If :cch:`derived$$$type` does override, it overrides 2 functions from different virtual function chains.

Try the example below with and without commented function in :cch:`derived$$$type`.

.. cch::
    :code_path: virtual_function_same_name.cpp
    :color_path: virtual_function_same_name.color

Interface vs implementation
###########################

Compared to other programming languages, inheritance in C++ allows much more. There are no constraints other than these which come from logic in mathematics - e.g. a loop within inheritance is not possible (in code there is even no way to express that due to ODR).

Many other languages impose specific limitations: there are separate :cch:`class` and :cch:`interface` keywords:

- an :cch:`interface` offers reduced functionality of an abstract class: it can not have data members, all functions must be virtual or (in some languages) all functions must be pure virtual
- a :cch:`class` can inherit from many :cch:`interface`\ s but only from 1 other :cch:`class`

This creates a framework where a class can inherit data and non-virtual functions only from 1 parent. Inheriting from an :cch:`interface` is called *interface inheritance* and inheriting from a :cch:`class` is called *implementation inheritance*. In Java this is further signified by the syntax :cch:`class identifier implements identifier$$$keyword spec keyword spec` (*interface inheritance*) and :cch:`class identifier extends identifier$$$keyword spec keyword spec` (*implementation inheritance*).

Why impose such limitation? Practice has shown that reasonable data-member-multiple-inheritance is very rare. It simply doesn't make sense in vast majorty of cases and leads to unmaintainable code.

- *Implementing* an interface? Sure - the type agrees to perform certain things (in *design by contract* terminology the interface definition is the contract).
- *Implementing* multiple interfaces? Not a problem, a class can satisfy multiple "contracts" (interfaces).
- *Extending* an existing class? Sure, seems very natural. Just a class that offers additional functionality.
- *Extending* multiple classes at once? This seems weird. You can *act* as multiple, different things but you can't *be* multiple, different things.

Another good example are games. Games almost always have huge amount of interactions. After all, by design players are expected to use these interactions to their advantage as much as possible. Various entities within a game can implement different abilities/functionalities (dealing damage, healing, changing statistics of other entities) - specifications of these functionalities would be *interfaces*. But an entity (NPC, enemy, item, interactable terrain object) can at most extend other entity (upgraded item), it can not *be* multiple entities at once.

Interface classes allow to write code that specifies certain expectations of behavior of a class and a class can implement multiple such specifications. Because interface classes do not carry any data with them (other than vtable pointers), there are no concerns about breaking invariants within derived types. Code that relies on these expectations does not need to know what data members are present - only the set of functions that can be called.

Example interface class:

.. cch::
    :code_path: example_interface_class.cpp
    :color_path: example_interface_class.color

Each derived class can implement logging very differently: standard output, output to file, over network, ignoring all calls (a "null logger" could be useful for some unit tests and benchmarking main code). Code that calls the logger doesn't care how it's done exactly - it only cares that it sends information to the logger.

In many cases when there seems to be a need for multiple implementation inheritance, *composition* should be used instead. Still there are situations (very rare) where the best way to solve the problem is to use multiple implementation inheritance.

Conventions
###########

Even though C++ has no :cch:`interface` keyword, the term *interface* or *interface class* can still be found being used in the comunity. For C++ it simply means a class with no non-static data members and all or most functions being virtual or pure virtual (non-virtual functions can be extra overloads for default parameters functionality).

In some other languages there are conventions for class names based on their purpose:

- non-interface class: ``Foo``, ``CFoo``
- interface class: ``FooInterface``, ``IFoo``
- exception: ``EFoo``, ``FooException``

There are no such conventions in C++ (see names in `the hierarchy of standard exception types <https://en.cppreference.com/w/cpp/error/exception>`_) though some frameworks do use it (e.g. Unreal Engine).

Design patterns
###############

If all of this still sounds unclear to you - don't worry. It will come with practice. I encourage you to look into *design patterns* after you finish this chapter (or later, after full C++ tutorial) - they showcase how and why specific approaches of using inheritance, access control, and (pure) virtual functions create (or not create) high-quality code. *Design patterns* are basically well-known specific combinations of OOP features that practice has proven to be working well. A lot of OOP code follows these patterns or mixes them together.

.. TOINCLUDE (in design patterns main page)

Knowing design patterns will:

- let you write well-known implementations with best possible tradeoffs of a solution to a particular problem
- write code that is easy to understand and maintain for others
- help you quickly understand unfamiliar code

----

More info:

- https://stackoverflow.com/questions/995255/why-is-multiple-inheritance-not-allowed-in-java-or-c
- https://stackoverflow.com/questions/406081/why-should-i-avoid-multiple-inheritance-in-c
- https://stackoverflow.com/questions/225929/what-is-the-exact-problem-with-multiple-inheritance
- https://docs.microsoft.com/en-us/archive/blogs/csharpfaq/why-doesnt-c-support-multiple-inheritance
