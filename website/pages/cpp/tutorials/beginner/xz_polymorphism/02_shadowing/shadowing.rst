.. title: 02 - shadowing
.. slug: index
.. description: shadowing members in derived classes
.. author: Xeverous

Just like entities declared in nested scopes *shadow* other entities with the same name, analogical thing happens in derived classes.

Data member shadowing
#####################

.. cch::
    :code_path: data_member_shadowing.cpp
    :color_path: data_member_shadowing.color

Obviously you should avoid such name conflicts, but sometimes you will have no control over external code. It's no so rare that the base class comes from a different project. Many libraries and frameworks expect their users to use inheritance to implement specific things.

Overload shadowing
##################

Shadowing also applies to function overloads. By default, functions with the same name will be hidden in derived type.

.. cch::
    :code_path: overload_shadowing.cpp
    :color_path: overload_shadowing.color

This surprising "feature" may have some niche uses but more often than not such behavior is unwanted. Imagine a situation where a base type overload accepts :cch:`int` and derived type overload accepts :cch:`long`. Because both are integers and promotion is an implicit convertion, a lot of code can match both overloads. Minor details like changing how you refer to the object (reference to base or derived type) will affect which overload is choosen, silently breaking existing code without any warning.

The actually desirable behavior (calling specific function implementation based on *dynamic type* of the object) are *virtual functions* which are explained later.

The problem can be solved by using using-declarations inside class definition.

Using-declarations inside classes
#################################

Classes aren't namespaces but using-declarations can be used to manipulate access level and overload resolution.

Function and data members
=========================

The declaration has 2 effects:

- it redefines access level to the entity
- for functions, it merges overloads that aren't exactly the same into one set

.. cch::
    :code_path: using_declarations_members.cpp
    :color_path: using_declarations_members.color

Redefining access is against OOP principles and I haven't heard of this ability in other languages. I guess the only reasonable use would be to allow access to specific member functions from types derived in non-public way (which again is a C++-specific feature).

Merging overload sets into one is fine, this actually brings behavior to the expectation that derived types extend the base type, not overwrite it.

.. admonition:: tip
  :class: tip

  When adding function overloads in derived classes, write a using declaration so that overloads form one set instead of hiding base class overloads (in case of multiple levels of inheritance, this action has to be repated in every class along the hierarchy that adds new overloads).

Constructors
============

Using-declarations can also be used for *direct base* constructors. In such case the current class works as if it had identical constructor overloads and just forwarded everything to the base type. This can save some boilerplate code when a new class doesn't have any additional initialization requirements (or they can use initializers in the class definition).

.. cch::
    :code_path: using_declarations_ctors.cpp
    :color_path: using_declarations_ctors.color

In this specific case of using-declarations, access specifiers are ignored. Accessibility level of each constructor overload is copied from the base type.

There are more nuances and corner cases than described here, you can read https://en.cppreference.com/w/cpp/language/using_declaration#Inheriting_constructors for additional examples but you don't have to remember them because code presented there is hardly ever written.

    How about using declarations for overloaded operators?

They are valid too, though very rare. The syntax and rules follow using declarations for data and function members. The most common one is :cch:`using base_type::operator=;`. It appears usually within templates that perform certain implementation tricks based on inheritance (not really a topic for this tutorial).
