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

*Enumerations* are an example of *user-defined types* - types not defined by the language but created in code by the user of the language (here *user* means programmer). Specific values of given enumeration are *enumerators*.

Convertions
###########

Enumerations are *implicitly convertible* to integers (but not in reverse). The rules for values are:

- unless explicitly specified, each enumerator has value of the previous one + 1
- unless explicitly specified, the first enumerator has value 0
- there can be multiple enumerators with the same value
- there can be gaps within the value range

.. mention std::endian?

..

    Can I convert an enum to/from a string?

Sadly no. Compared to other languages, :cch:`enum`\ s in C++ are pretty basic - they are just a different form of writing constants with some added type safety. If you want more features, use a library like `Better Enums <https://github.com/aantron/better-enums>`_.

:cch:`enum class`
#################

C++11 added *scoped enumerations*, sometimes called *strongly typed enumerations*. They are defined with :cch:`enum class` or :cch:`enum struct` (both equivalent but the former became the convention) and have 2 important differences:

- They are not implicitly convertible to/from integers. :cch:`static_cast` must be used in both directions.
- Enumerators must be accessed using the *scope resolution operator* (:cch:`::`)

.. example

.. admonition:: note
  :class: note

  :cch:`enum class` and :cch:`enum struct` do not create a :cch:`class` or a :cch:`struct`. These keywords here are only used to differentiate them from pre-C++11 enums which have much more relaxed rules.

Recommendation
##############

- Use :cch:`enum` when you have a group of related constants and each represents one of possibilities. Especially if values are going to be passed to functions.
- Explicit values of enumerators should be only specified when there is a need to convert them to/from integers.
- Enumerators with the same value generally should be avoided (it's kind of duplicate code) but they are useful in certain situations:

  - Backwards compatibility: old name can still function while being equivalent to the new name.
  - Future proofing: multiple enumerators can be introduced and if it's realized later that situations they denote are identical, values can be equivalent.
  - Clarity: in cases when there is a finite amount of things that could happen and some require the same reaction. Listing them all is still valuable - otherwise someone reading the code could think that some were forgotten.
