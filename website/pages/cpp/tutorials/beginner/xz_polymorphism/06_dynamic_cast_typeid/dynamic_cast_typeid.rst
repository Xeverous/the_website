.. title: 06 - dynamic_cast and typeid
.. slug: index
.. description: dynamic_cast, typeid and RTTI
.. author: Xeverous

You already know that pointers/references to derived types can be implicitly converted to their base types - after all, they are extensions of them so a cast doesn't do anything special, the abstraction will simply refer to a smaller block of memory.

However, what if we would like to do the reverse? Is it even possible?

Downcasts
#########

A situation like this might appear in some code:

.. cch::
    :code_path: motivation.cpp
    :color_path: motivation.color

First of all, **downcasts are against OOP principles**. The code above should be refactored to use a virtual function which is implemented in derived classes. Then there is no need for checking actual (dynamic) type of the object. The whole point of virtual functions is that you do not care what the dynamic type is. Downcasts are an example of `code smell <https://en.wikipedia.org/wiki/Code_smell>`_.

Still, if you really want to do (ugly) downcasts, there are 2 ways: :cch:`static_cast` and :cch:`dynamic_cast`.

Static downcasts
================

Just like upcasts don't do anything (except when *virtual inhertance* is used), so do downcasts. But there is a problem: in case of upcasts it's known at compile time that a given class has a base class. But in the case of downcasts, it's not known what the dynamic type of the object is (and multiple different types can inherit from the same base type). :cch:`static_cast<cat&>(a)$$$keyword<type&>(param)` is valid, but will only succeed if the dynamic type of the object is :cch:`cat$$$type` or something derived from it. **If not, it will invoke undefined behavior.**

Downcasts using :cch:`static_cast` can be performed on both references (e.g. from :cch:`animal&$$$type&` to :cch:`cat&$$$type&`) and pointers (e.g. from :cch:`animal*$$$type*` to :cch:`cat*$$$type*`). In both cases, the code must guuarantee through other means that the object is in fact of derived type to avoid undefined behavior. This is usually done by calling a virtual function before the cast that indicates object's dynamic type - a common approach is to return an enumerator.

In case of pointers, if the input pointer is a *null pointer*, the result is also a *null pointer* (no undefined behavior).

Dynamic downcasts
=================

Unlike :cch:`static_cast`, :cch:`dynamic_cast` performs a runtime check to avoid undefined behavior. In order for this to work, the input class to the cast has to be *polymorphic* (that is, contain at least 1 :cch:`virtual` function). Otherwise the program is *ill-formed*.

How does the check work? Polymorphic types contain vtable pointer and the table (apart from addresses of virtual function implementations) contains additional metadata known as **RTTI** (`run-time type information <https://en.wikipedia.org/wiki/Run-time_type_information>`_). Based on this information, :cch:`dynamic_cast` can check whether the cast is valid.

If the cast is not valid:

- if performed on pointers, *null pointer* is returned
- if performed on references, an exception is thrown of type :cch:`std::bad_cast` or a type derived from it

.. TODO exceptions when?

Since exceptions are a quite heavy mechanism intended primarily for error handling, typical dynamic downcasts are performed on pointers. Using exceptions for type casting is considered an overcomplication.

Here is example code that showcases all approaches:

.. cch::
    :code_path: downcast.cpp
    :color_path: downcast.color

RTTI
####

The :cch:`type_info$$$func` function in the example above can be thought as a way of implementing manual RTTI. Many different approaches are possible, another simple one being an additional parameter in :cch:`animal$$$type` constructor of type :cch:`animal_type_info$$$type` - derived types would have to supply an appropriate enumerator value. This approach would move the implementation from virtual function to a non-virtual function + extra data member in the base class.

Which approach is the best depeds on a lot of factors:

- runtime efficiency (time of performing type checks)
- memory efficiency (extra members will mean larger memory usage)
- binary size (more and larger vtables means potentially worse cache usage)
- simplicity and maintainability of implementation

The language-built-in implementation is the simplest to maintain (no additional code is required - :cch:`dynamic_cast` just works) but often has the largest binary size, memory and efficiency impact. Compilers offer options like ``-fno-rtti`` to disable this feature (RTTI-requiring :cch:`dynamic_cast` becomes unusable in such case) if it's not needed (disabling RTTI will reduce binary object size).

:cch:`typeid`
#############

:cch:`typeid` is a keyword that returns a reference to RTTI of the given type, specifically the keyword acts like a function that has return type :cch:`const std::type_info&` (this means it can actually return an object of a type derived from :cch:`std::type_info`). Just like :cch:`sizeof` and :cch:`alignof`, it can be called with both type and value expressions. Because the keyword returns a const reference to the type info class:

.. admonition:: note
  :class: note

  The header :cch:`<typeinfo>` must be included before using :cch:`typeid`. Otherwise every use of the keyword is ill-formed.

For :cch:`typeid`, the type (not necessarily a class) **does not have to** be polymorphic. It can be any *complete* type - for non-polymorphic types it will simply return information about the *static type* of the object. If the type is polymorphic, :cch:`typeid` will access object's vtable and read RTTI from it.

:cch:`std::type_info` is documented on https://en.cppreference.com/w/cpp/types/type_info. Given that the class has a comparison operator, it's possible to implement another form of safe static downcast using this keyword:

.. cch::
    :code_path: typeid_downcast.cpp
    :color_path: typeid_downcast.color

It's likely that the code above produces very similar machine code as downcasts with :cch:`dynamic_cast`. The only behavioral difference is that :cch:`typeid` checks the type identification for exact match while :cch:`dynamic_cast` checks whether type dynamic type of the object is of the destination type or a type derived from it.

Summary
#######

Avoid downcasts - they indicate flawed design. Use them only if there is no better way.

.. TOINCLUDE cheatsheets

Small cheatsheet of casts over class hierarchies (note: this table assumes there is no virtual inheritance):

.. list-table::
  :header-rows: 1

  * - cast
    - implicit convertion
    - :cch:`static_cast`
    - :cch:`dynamic_cast`
  * - upwards (always succeeds)
    - well-defined behavior
    - unnecessary
    - unnecessary
  * - downwards (success)
    - ill-formed
    - well-defined behavior
    - well-defined behavior
  * - downwards (failure)
    - ill-formed
    - undefined behavior
    - well-defined behavior
