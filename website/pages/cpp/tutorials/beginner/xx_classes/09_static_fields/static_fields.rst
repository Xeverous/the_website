.. title: 09 - static fields
.. slug: index
.. description: class static data members
.. author: Xeverous

As stated in a previous chapter, :cch:`static` modifies object's *storage duration*.

A class can contain :cch:`static` members: variables (fields) and functions (methods). :cch:`static` fields, unlike other :cch:`static` objects do not have reduced linkage. They can still be used in other TUs.

*This lesson uses structures in examples to simplify and shorten code.*

.. admonition:: definition
  :class: definition

  :cch:`static` members are not tied to any particular instance of the class. They are shared for all instances.

Said differently, :cch:`static` fields are just global objects that are placed inside class namespace.

.. cch::
    :code_path: example.cpp
    :color_path: example.color

.. code::

    f1.s = 1
    f2.s = 1
    f1.s = 2
    f2.s = 2
    address of f1.s = 0x600eb8
    address of f2.s = 0x600eb8
    sizeof(int) = 4
    sizeof(foo) = 4
    foo::s = 3

Because :cch:`static` member objects are global it's recommended to refer to them through the class name, not specific objects. The syntax which uses ``.`` helps in some situations (e.g. templates which don't know on what type they operate) but can be misleading.

In practice
###########

Obviously global state is bad so :cch:`static` fields should be avoided. A typical example where they can be used is generation of unique IDs:

.. cch::
    :code_path: user_id.cpp
    :color_path: user_id.color

Here each :cch:`user$$$type` object will get a unique ID. The :cch:`id$$$var_member` member could be :cch:`const`, but there are good reasons to not use the keyword even if the field never changes (the main one being prevention of assignment of objects of this class).

Static initialization order fiasco
##################################

The same fiasco can happen with :cch:`static` members:

.. cch::
    :code_path: siof.cpp
    :color_path: siof.color

.. admonition:: error
  :class: error

  The order of initialization across TUs is *undefined*, so the program above has **undefined behavior**!

The solution is the same as with other :cch:`static` objects - bundle them together into one type and move :cch:`static` from these objects to the instance of this type:

.. cch::
    :code_path: siof_fixed.cpp
    :color_path: siof_fixed.color

Syntax sugar
############

There are ways to avoid the need of initialization outside the class definition:

.. cch::
    :code_path: syntax_sugar.cpp
    :color_path: syntax_sugar.color

The C++17 improvement is most significant, because it completely removes the need to write initialization of :cch:`static` fields outside class definition. Apart from shorter code, it eliminates a common mistake when the initialization was simply forgotten.

Summary
#######

- :cch:`static` fields are affected by access specifiers (except initialization statement).
- :cch:`static` fields are not associated with any object. They exist even if no objects of the class have been created.
- :cch:`static` fields can not be :cch:`mutable`.
- :cch:`static` fields can also be declared :cch:`thread_local`.
- :cch:`static` fields are initialized before :cch:`main` starts executing.

..

    Does it mean that through constructor of a static object I can inject a function to be run before main?

Yes. Obviously this should not be abused. Order of intialization of objects with *static storage duration* is *undefined* but C++ guarantees that standard library objects are initialized first - this means that you can use :cch:`std::cout` before :cch:`main` starts executing.
