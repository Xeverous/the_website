.. title: casts
.. slug: index
.. description: explicit cast keywords in C++
.. author: Xeverous

.. admonition:: note
    :class: note

    All casts in this article are forms of *explicit convertion*. Implicit convertion is explained in a different article.

In many languages, the syntax to convert an object is :cch:`(T) expression` or :cch:`T(expression)`. Both are also valid in C++ (for backwards compatibility), but **discouraged**.

C++ has 4 keywords dedicated for casts, each with distinct behavior. In C++11 they have been modernized. Why all of these? There are multiple reasons:

- C++ is a complex language that can work on multiple levels of abstraction. There are situations where multiple ways of converting an object are possible so a single way of writing is not enough.
- Cast keywords are very clear about their intent.
- Cast keywords produce better compiler errors because each has narrowed set of rules.
- It's easy to make a mistake with old casts, including ones that invoke undefined behavior.
- One of old casts has a grammar problem - it accepts only *simple-type-specifier* or a *typedef-specifier* (less technically: a single-word type name), for example :cch:`long long(expression)$$$keyword keyword(spec)` and :cch:`int*(expression)$$$keyword*(spec)` are not valid.

Old casts
#########

- Casts inherited from C, they take the form :cch:`(T) expression`.
- *functional cast expressions* (not present in C), they take the form :cch:`T(expression)`. Depending on the type, the same syntax can also mean a constructor call.

Both of these work the same (apart from grammar issues which block some usages). Put shortly, they will pick behavior identical to one of keyword casts. The picking `is quite complex <https://en.cppreference.com/w/cpp/language/explicit_cast>`_ and `there is an article describing a case where included files can affect behavior <https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/>`_. You certainly do not want to experience undefined behavior just because of changes in some (potentially transitively) included header files.

So ... simply don't use these casts in C++11 (and later) code. The only widely accepted old cast is explicit discard of the result: :cch:`(void) expression`. It relies on the fact that anything can be converted to void type - this cast should be used purely to shut warnings about unused variables (usually unused function parameters when commenting out name is not feasible if they are used on a different build configuration - different target platform or debug/release).

Cast keywords
#############

The cast keywords are:

- :cch:`static_cast<T>(expression)`
- :cch:`dynamic_cast<T>(expression)`
- :cch:`const_cast<T>(expression)`
- :cch:`reinterpret_cast<T>(expression)`

Apart from solving ambiguity and code clarity problems, a big advantage of these keywords is that they look exactly like function templates - new casts can be added with the same syntax. Some already exist:

- C++20 :cch:`std::bit_cast` - obtains value of type :cch:`T` by reinterpreting object representation. This could be thought as a short form of specific usage of :cch:`reinterpret_cast` but the bit cast guuarantees no *aliasing* violations while the keyword alone does not. It's also :cch:`constexpr`.
- :cch:`boost::lexical_cast` (string to number and number to string)
- :cch:`boost::numeric_cast` (number to number)

:cch:`static_cast`
##################

The keyword is used for all typical convertions that rely on compile time information. It's by far the most used explicit convertion keyword.

The cast does not modify the source object, it creates a new object thus the source object can be :cch:`const`. Possible convertions:

- all implicit convertions
- :cch:`enum` to :cch:`bool`, integer or floating-point type and reverse of it
- bit-field to its underlying type
- anything to :cch:`void` (usually to shut compiler warnings about unused variables)
- constructor calls if the destination type is a class, additional implicit convertions are allowed in such case
- call to user-defined convertion operator - classes can overload :cch:`operator T` to enable such convertions, many overload :cch:`explicit operator bool` to support code like :cch:`if (obj)`
- pointer/reference inheritance casts (these only create a new pointer/reference, they do not modify the pointed/referenced object)
- (possibly cv-qualified) :cch:`void*` to any pointer to an object type (function pointers are not object pointers) that is not less cv-qualified

Enumerations
============

An integer or floating point may be converted to :cch:`enum` even if the enumeration has no such value. It will not be adjusted and will compare :cch:`false` with any enumerator. If the :cch:`enum` has no fixed underlying type, the largest allowed value is the is the largest representable value in the smallest bitfield capable of holding enumeration values.

.. cch::
    :code_path: static_cast_enum.cpp
    :color_path: static_cast_enum.color

Type upcasts
============

A pointer/reference to derived class may be converted to a pointer/reference to the base class.

- the cast is *ill-formed* if base is ambiguous (multiple inheritance can result in one type being inherited from multiple times)
- the cast is *ill-formed* if base is inaccessible (private or protected inheritance)
- if the pointer is null the resulting pointer is also null

.. cch::
    :code_path: static_cast_upcast.cpp
    :color_path: static_cast_upcast.color

.. admonition:: note
    :class: note

    These upcasts can also be performed implicitly.

Type downcasts
==============

A pointer/reference to base class may be converted to a pointer/reference to the derived class.

.. admonition:: error
    :class: error

    No runtime checks are performed to check that the pointed/referenced object is actually of the derived type. If it's not, the behavior is undefined. If checks are needed, :cch:`dynamic_cast` should be used.

The cast has same ambiguity and accessibility preconditions as the upcast, but additionally the cast is *ill-formed* if base is a virtual base or a base of virtual base of derived - in such case :cch:`dynamic_cast` is needed.

.. cch::
    :code_path: static_cast_downcast.cpp
    :color_path: static_cast_downcast.color

Because of undefined behavior risk, :cch:`static_cast` downcasts must guuarantee through other means that the object is in fact of derived type - usually the base class has a :cch:`virtual` method which returns unique value for each type (basically manual and simplified implementation of RTTI).

Member pointer upcasts
======================

A pointer to member of derived class can be converted to a pointer to member of the base class. **The cast makes no checks to ensure the member actually exists in the runtime type of the pointed-to/referenced object.**

- the cast is *ill-formed* if base is ambiguous
- the cast is *ill-formed* if base is inaccessible
- if the pointer is null the resulting pointer is also null

.. cch::
    :code_path: static_cast_mp_upcast.cpp
    :color_path: static_cast_mp_upcast.color

Member pointer downcasts
========================

A pointer to member of base class can be converted to a pointer to member of the derived class.

- the cast is *ill-formed* if base is ambiguous
- the cast is *ill-formed* if base is inaccessible
- the cast is *ill-formed* if base is a virtual base or a base of virtual base of derived class
- if the pointer is null the resulting pointer is also null

.. admonition:: note
    :class: note

    These upcasts can also be performed implicitly.

More on pointers
================

.. TODO move pointer convertions to pointers chapter? This article deals with inheritance only but pointers have many more convertions (void*, interconvertibility, aliasing, cv-qualifiers)

.. TODO mention: Static casts can not be used for int-to-string or string-to-int convertions since they involve a class type. Standard library offers multiple parsing functions instead.

.. admonition:: note
    :class: note

    Pointers to data members have the same convertion rules as pointers to function members.

.. admonition:: note
    :class: note

    Pointers to members are hardly ever used.

..

    I don't get why while pointer **upcasts** are implicit, pointer to member **downcasts** are implicit.

Pointer/reference upcasts are simple: every derived object also has a base subobject. Not so in reverse.

Pointer to member downcasts are safe because every derived class also has members of the base class. Not so in reverse.

Sidecasts
=========

Sidecasts with :cch:`static_cast` are not possible. An upcast has to be made first and then a downcast.

.. cch::
    :code_path: static_cast_sidecast.cpp
    :color_path: static_cast_sidecast.color

Overload sets
=============

One very practical use of :cch:`static_cast` is selecting a specific function overload to resolve an ambiguity.

.. cch::
    :code_path: static_cast_overload_set.cpp
    :color_path: static_cast_overload_set.color

It can be made even simpler by introducing a helper function template:

.. cch::
    :code_path: static_cast_select_overload.cpp
    :color_path: static_cast_select_overload.color

..

    Why there is no ``(&)`` in the second example?

The first example casts the function overload set to a reference to a function of specific type (a function type would be invalid because functions can not be taken by value), the second example has the reference built into the template.

    Why then the first function takes a function argument by value?

It's not a *function* but a *function template*.

    Why then the first function template takes a function argument by value?

It does not because it's a *function template* and the *template parameter* is a subject to *template type deduction*. The *deduced type* may be a *reference* type.

    Why is dedu...

Go learn templates in their dedicated tutorial!

:cch:`dynamic_cast`
###################

This keyword is intended for inheritance casts.

Like :cch:`static_cast`, this cast can also perform some convertions that are allowed implicitly (most notably upcast and adding cv-qualifiers).

Requirements
============

The result type can only be:

- pointer to class type
- reference to class type
- (possibly cv-qualified) :cch:`void*`

The input expression must be:

- reference to a class type if result type is a reference
- pointer to a class type if the result type is a pointer

The types involved must:

- be complete (forward declarations will result in compile errors)
- analogically to :cch:`static_cast`:

  - there must be no ambiguity
  - there must be no inaccessibility

- be polymorphic when performing a downcast or a sidecast (such casts perform a runtime check which involves some overhead and requires RTTI - enabled by default in most compilers)

If the cast is used on an object during construction or destruction and the result type is not a type matching the constructor/destructor or one of its bases, the behavior is undefined.

Results
=======

- If the result type is a pointer and the input pointer is null or cast fails the result is a null pointer.
- If the result type is a reference and the cast fails, an exception of type :cch:`std::bad_cast` or a type derived from it is thrown.

The pointer version is strongly preferred. Use the reference version when you don't expect the cast to fail.

Examples
========

.. cch::
    :code_path: dynamic_cast_inheritance.cpp
    :color_path: dynamic_cast_inheritance.color

.. cch::
    :code_path: dynamic_cast_ctor_dtor.cpp
    :color_path: dynamic_cast_ctor_dtor.color

Questions
=========

    What if RTTI is disabled?

Most compilers, if given ``-fno-rtti`` option (or equivalent) treat RTTI-requiring :cch:`dynamic_cast` expressions as ill-formed. For more information see typeof article TOWRITE.

    Are :cch:`static_cast` casts and :cch:`dynamic_cast` upcasts only an abstraction? Do they compile to any machine instructions?

They can. Apart from *padding* issues (caused by different *alignment* requirements) in case of :cch:`virtual` base classes (even with no :cch:`virtual` functions), the compiler may need to adjust :cch:`this` pointer to correctly point to a subobject of specified type.

:cch:`const_cast`
#################

This cast can unconditionally add or remove :cch:`const` and/or :cch:`volatile` on:

- references
- (potentially multilevel) pointers
- (potentially multilevel) pointers to data members
- (potentially multilevel) pointers to arrays of known bound
- (potentially multilevel) pointers to arrays of unknown bound

Pointers to functions and pointers to member functions are not subject to :cch:`const_cast`.

The cast is designed to workaround issues with legacy code, particulary C code before C imported :cch:`const` keyword from C++.

.. admonition:: error
    :class: error

    The cast allows to form non-const references/pointers to :cch:`const` objects and non-volatile references/pointers to :cch:`volatile` objects. Modifying a :cch:`const` object through a non-const access path and referring to a :cch:`volatile` object through a non-volatile *glvalue* results in undefined behavior.

In short, **while the cast allows to strip** :cch:`const` **and** :cch:`volatile`\ **, it still doesn't justify breaking related rules**. It's purely to interact with troublesome non-cv-qualifier-correct legacy code.

.. cch::
    :code_path: const_cast_legacy.cpp
    :color_path: const_cast_legacy.color

.. cch::
    :code_path: const_cast_objects.cpp
    :color_path: const_cast_objects.color

.. cch::
    :code_path: const_cast_functions.cpp
    :color_path: const_cast_functions.color

:cch:`reinterpret_cast`
#######################

Similarly to :cch:`const_cast`, :cch:`reinterpret_cast` does not compile to any machine instructions (except when converting between integers and pointers or on obscure architectures where pointer representation depends on its type). **It is purely a compile time directive which instructs the compiler to treat expression as if it had a different type.**

Because the cast allows to explicitly violate the type system (except :cch:`const` and :cch:`volatile` for which :cch:`const_cast` has to be used) and multiple implementation and platform shenanigans are in play, there are numerous rules that specify different requirements and guuarantees. The cast is used practically only for platform-specific code or code that relies on particular implementation guuarantees (larger than the standard).

The standard technically allows many obscure platforms, but in practice many (if not majority or all) platforms have relatively simple pointer implementation where:

- :cch:`sizeof(void*) == sizeof(T*)$$$keyword(keyword*) == keyword(tparam*)` for any :cch:`T`
- :cch:`sizeof(void*) == sizeof(std::uintmax_t)$$$keyword(keyword*) == keyword(namespace::type)`
- :cch:`sizeof(void*) == sizeof(std::uintptr_t)$$$keyword(keyword*) == keyword(namespace::type)`
- :cch:`alignof(void*) == alignof(std::uintptr_t)$$$keyword(keyword*) == keyword(namespace::type)`
- :cch:`std::uintmax_t` and :cch:`std::uintptr_t` are the same type
- :cch:`void*` can be safely converted to and from non-member function pointers.

Note that pointers to member functions are not the same as pointers to free functions as the former have to support :cch:`virtual` functions and multiple inheritance. Such pointers typically hold multiple addresses and/or offsets. `Relevant SO question. <https://stackoverflow.com/q/12006854/4818802>`_

Integral convertions
====================

- A pointer can be converted to any integral type large enough to hold all values of its type.
- A value of any integral or enumeration type can be converted to a pointer type. A pointer converted to an integer of sufficient size and back to the same pointer type is guaranteed to have its original value, otherwise the resulting pointer cannot be dereferenced safely (the round-trip conversion in the opposite direction is not guaranteed; the same pointer may have multiple integer representations).

This is simple. Pointers are just memory addresses (the pointed type is purely an abstraction information for the compiler) so their values can aswell be held by integral types. If implementation supports it, :cch:`<cstdint>` delivers :cch:`std::uintptr_t` (not a separate type but an alias, usually for :cch:`unsigned long long`) which is capable of holding pointers to :cch:`void`. There is also :cch:`std::intptr_t` but I have never seen anyone using it, :cch:`signed` integral just doesn't seem right here. I recommend to use :cch:`std::uintptr_t` if it's available because the name clearly specifies intention.

.. This is left unmentioned - seems to have no practical/meritorical value
.. Any value of type std::nullptr_t, including nullptr can be converted to any integral type as if it were (void*)0, but no value, not even nullptr can be converted to std::nullptr_t: static_cast should be used for that purpose.

- An expression of integral, enumeration, pointer, or pointer-to-member type can be converted to its own type. No changes in value.

I guess this exists to support templates using :cch:`reinterpret_cast` which accidentally invoke identity convertions in instantiations for some types.

Pointer convertions
===================

- A pointer to member function can be converted to pointer to a different member function of a different type. Conversion back to the original type yields the original value, otherwise the resulting pointer cannot be used safely.
- A pointer to member object of some class :cch:`T` can be converted to a pointer to another member object of another class :cch:`U`. If alignment of :cch:`U` is not stricter than alignment of :cch:`T` (that is, :cch:`alignof(U) <= alignof(T)$$$keyword(tparam) <= keyword(tparam)`), conversion back to the original type :cch:`T` yields the original value, otherwise the resulting pointer cannot be used safely.
- Any pointer to function can be converted to a pointer to a different function type. Calling the function through a pointer to a different function type is undefined, but converting such pointer back to pointer to the original function type yields the pointer to the original function.
- On some implementations, a function pointer can be converted to :cch:`void*` or any other object pointer, or vice versa. If the implementation supports conversion in both directions, conversion to the original type yields the original value, otherwise the resulting pointer cannot be dereferenced or called safely.

The last point is `required on any POSIX compatible system <http://pubs.opengroup.org/onlinepubs/9699919799/functions/dlsym.html>`_ because :cch:`dlsym$$$func` returns pointers to dynamically loaded objects which may be functions.

Aliasing casts
==============

These are the primary uses of :cch:`reinterpret_cast`. They create references/pointers which *alias* an existing object and allow access to its byte representation.

.. admonition:: error
    :class: error

    :cch:`reinterpret_cast` alone does not justify violating *aliasing rules*. Only certain types are allowed to *alias* each other. Any technique that is seemingly capable of creating a situation where two pointers to different types that are not exempt from *strict aliasing* could simultaneously exist (and both can be used to load or store the same memory) necessarily invokes undefined behavior.

    For an explanation about *strict aliasing* see its dedicated article TOWRITE.

- Any object pointer type :cch:`T*` can be converted to another object pointer type :cch:`cv U*$$$spec tparam*`. This is exactly equivalent to :cch:`static_cast<cv U*>(static_cast<cv void*>(expression))$$$keyword<spec tparam*>(keyword<spec keyword*>(spec))`, which implies that if alignment of :cch:`U` is not stricter than alignment of :cch:`T` (that is, :cch:`alignof(U) <= alignof(T)$$$keyword(tparam) <= keyword(tparam)`), the value of the pointer does not change and conversion of the resulting pointer back to its original type yields the original value.
- An *lvalue* expression of type :cch:`T` can be converted to reference to another type :cch:`U`. The result is an *lvalue* or *xvalue* referring to the same object as the original *lvalue*, but with a different type. No temporary is created, no copy is made, no constructors or conversion functions are called.

Summary
#######

- use :cch:`static_cast` for:

  - converting between different types of data (usually numeric)
  - downcasting when it's known that the object if of derived type

- use :cch:`dynamic_cast` for downcasts and sidecasts when *dynamic type* of the object is not known
- use :cch:`const_cast` for dealing for non-cv-qualifier-correct interfaces
- use :cch:`reinterpret_cast` for:

  - inspecting object representation
  - interacting with low-level facilities
  - pointer-integer convertions
