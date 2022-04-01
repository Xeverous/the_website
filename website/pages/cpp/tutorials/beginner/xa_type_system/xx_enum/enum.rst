.. title: ?? - enum
.. slug: index
.. description: enumeration types
.. author: Xeverous

.. TOEXAMPLE

You already know that *magic numbers* are bad.

.. example with magic numbers

It's much better to use named constants - they increase code readability.

.. example with named constants

It's quite common to have a few closely related constants. To signal that they are related, we could add a common name prefix but this still doesn't prevent of mistakes like this:

.. example with function taking int, given constant from wrong set

There is a dedicated feature for a group of constants:

.. example enum - definition and usage, showcase last ,

*Enumerations* are an example of *user-defined types* - types not defined by the language but created in code by the user of the language (here *user* means programmer). Specific values of given enumeration are called *enumerators*. Enumerations are *implicitly convertible* to integers.

Enumerations were already present in C. The feature is relatively simple, not much more than just a syntax sugar for specifying constants. There are 2 particular problems caused by this simplicity:

.. cch::
    :code_path: enum_problems.cpp
    :color_path: enum_problems.color

..

    Why the function call here is not a compiler error?

The enum is implicitly converted to an integer and then this integer is implicitly converted to a different enumeration type.

:cch:`enum class`
#################

C++11 added *scoped enumerations*, sometimes called *strongly typed enumerations*. They are defined with :cch:`enum class` or :cch:`enum struct` (both equivalent but the former became the convention) and solve the just mentioned problems:

- They behave as proper types: enumerator names from different :cch:`enum class` definitions do not conflict and names must be accessed using the *scope resolution operator* (:cch:`::`)
- They are not implicitly convertible to/from integers. Use :cch:`static_cast` to do so. As a consequence, mismatched enumeration types (e.g. when calling a function) will cause compiler errors.

.. cch::
    :code_path: enum_class.cpp
    :color_path: enum_class.color

.. admonition:: note
  :class: note

  :cch:`enum class` and :cch:`enum struct` do not create a :cch:`class` or a :cch:`struct`. These keywords here are only used to differentiate them from pre-C++11 enums which have much more relaxed rules.

Enumerator values
#################

- unless explicitly specified, each enumerator has value of the previous one + 1
- unless explicitly specified, the first enumerator has value 0
- there can be multiple enumerators with the same value
- there can be gaps within the value range

.. cch::
    :code_path: enum_values.cpp
    :color_path: enum_values.color

Underlying type
###############

Since enumerations are an abstraction over constant integers, it's possible to specify on which *integral* type they should be implemented:

.. cch::
    :code_path: underlying_type.cpp
    :color_path: underlying_type.color

.. admonition:: note
  :class: note

  The default underlying type is:

  - :cch:`int` for scoped enumerations (defined inside a function or a class)
  - *implementation-defined* for unscoped enumerations (defined in global scope)

Since C++11 the standard library contains a *type trait* that can be used to obtain enumeration's underlying type. Since C++23 there is also a function that converts the enumeration to its udnerlying type. Below I present a C++11-compatible implementation of this function. With such function, you can easily and safely convert enumerations to their underlying types with minimal effort.

.. cch::
    :code_path: to_underlying.cpp
    :color_path: to_underlying.color

Convertions in detail
#####################

- If the :cch:`enum` or :cch:`enum class` has specified *underlying type*, then all convertions to/from act as if the enumerator had value of this type.
- If the *underlying type* is not specified, the largest allowed value is the largest representable value in the smallest bitfield capable of holding enumeration values. No overflow, just undefined behavior.
- It's possible to convert a value of integral type to an enumeration type where no enumerator has such value. Object of the enumeration type will simply compare :cch:`false` with every enumerator.

.. TOPASTE static_cast_enum.cpp

    What's the reason behind smallest possible bitfield for enums with no underlying type?

No idea. In theory, it allows the compiler to use less bits than required by the type but no compiler actually does such optimization - first, you can't have :cch:`sizeof` which is not a multiple of whole bytes, second, saving space this way complicates read/write instructions and in today's world we have much higher pressure on computing time, not memory. Some optimizations even intentionally cause the code to occupy more space in order to speed up execution (e.g. ``-falign-functions``).

    Can I convert an enum to/from a string?

Sadly no. Compared to other languages, :cch:`enum`\ s in C++ are pretty basic - they are just a different form of writing constants with some added type safety. If you want more features, use a library like `Better Enums <https://github.com/aantron/better-enums>`_ which offers a macro that defines enumerations and the boilerplate needed to match strings with enumerators.

Recommendation
##############

- Use :cch:`enum class` istead of :cch:`enum`.
- Use enumerations when you have a group of related constants and each represents one possibility (which exludes others).
- Explicit values of enumerators should be only specified when there is a need to convert them to/from integers.
- Enumerators with the same value generally should be avoided (it's kind of duplicate code) but they are useful in certain situations:

  - Backwards compatibility: old name can still function while being equivalent to the new name.
  - Future proofing: multiple enumerators can be introduced and if it's realized later that situations they denote are identical, values can be equivalent (**differently named enumerators with the same assigned value compare equal**).
  - Clarity: in cases when there is a finite amount of things that could happen and some require the same reaction. Listing them all is still valuable - otherwise someone reading the code could think that some were forgotten.

Additional resources
####################

- `SO: Why is enum class preferred over plain enum? <https://stackoverflow.com/q/18335861/4818802>`_
