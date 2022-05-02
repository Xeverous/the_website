.. title: xx - variadic arguments
.. slug: index
.. description: ellipsis, printf family of functions and why not to use it
.. author: Xeverous

.. TOINCLUDE

.. admonition:: note
  :class: note

  This lesson is optional. It showcases a C++ feature imported from C, mainly for backwards compatibility. Variadic arguments shouldn't be used in C++ (`CG ES.34 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-ellipses>`_) - there are far better alternatives.

Sometimes there is a desire to provide varying amount of arguments to a function. Arrays (objects composed of multiple subobjects of the same type) could be used for this purpose but they are limited to one type.

Variadic arguments (often referred to as *va-args*) allow to pass an arbitrary amount of objects of a limited set of types to a function through a magic :cch:`...` argument. By far, the most well-known and the most utilized functions with variadic arguments is the printf family of functions from the C standard library (also available in C++):

.. cch::
    :code_path: printf_family.hpp
    :color_path: printf_family.color

All functions take a string which specifies formatting and a variadic set of arguments. All functions return the number of printed characters.

.. cch::
    :code_path: example.cpp
    :color_path: example.color

How it works
############

A function which accepts va-args is not aware how many arguments have been passed. Additionally, for implementation reasons (different size and alignment of different types):

- various built-in types undergo through a specific set of convertions:

  - :cch:`float` to :cch:`double`
  - :cch:`bool`, :cch:`char`, :cch:`short` and *unscoped enumerations* to :cch:`int`
  - few others for arrays, pointers and other kinds of types

- user-defined types are not supported or supported with *implementation-defined* semantics
- the behavior is undefined if the last parameter before :cch:`...` has reference type or is not supported in the set of convertions

In other words, arguments passed through magic :cch:`...` undergo various transformations so that the implementation can assume certain things about them. This greatly limits the set of allowed types, practically to only simple built-in types.

The function from the inside has to use a set of magic macros which can be roughly represented as such functions:

.. cch::
    :code_path: va_macros.hpp
    :color_path: va_macros.color

Again, for implementation reasons the macros have weird forms and expect the caller to know certain things about the parameters. This is why printf-family of functions requires to provide format strings like :cch:`%ld$$$0fmt` so that it knows how to extract actual data.

Even a simple function which adds numbers (assuming all are of type :cch:`int`) is fairly complicated:

.. cch::
    :code_path: add_nums.cpp
    :color_path: add_nums.color

Why it's bad
############

Variadic arguments, due to their design, cause numerous problems:

- They require to use macros, and in C++ macros should be used only as a last resort.
- These macros are "magic", they require compiler support to work and have unusual syntax.
- These macros are not even UPPERCASE, thus they violate a very strong convention.
- Everything related to their usage is extremely bug-prone: basically any mistake ends in undefined behavior.
- Even if a function with variadic arguments is perfectly written, it's still possible to call it with invalid parameters to invoke undefined behavior.
- Using functions with variadic arguments is not trivial, just see `printf documentation <https://en.cppreference.com/w/cpp/io/c/fprintf>`_.
- The set of supported types is limited.
- Supported types undergo through specific convertions.
- Even passing variadic arguments from one to another function is not trivial.
- There are no performance benefits.

In short, it's a very type unsafe feature with lots of opportunities to write dysfunctional code. The only benefit is the ability to pass an arbitrary amount of objects of different types, though many "terms and conditions" apply.

Variadic arguments are so bug-prone that **compilers implemented special warnings, just for the printf-family of functions**. They scan format strings and compare them with available compile time information about other arguments to detect potential mistakes. **It's a huge failure that statically typed languages such as C and C++ require the programmer to manually provide type information.**

Variadic arguments are simply against core C and C++ goals.

Alternatives
############

Due to complexity, risk and uintuitiveness of variadic arguments, everything else is better:

- function overloading - supports different types
- arrays - supports arbitrary amount of arguments
- :cch:`std::initializer_list` - an alternative to arrays
- (variadic) templates - they also use :cch:`...` but work totally differently

Libraries with formatting:

- `Boost.Format <https://www.boost.org/doc/libs/release/libs/format/doc/format.html>`_ (header-only): has printf-like interface but is implemented through templates and has full type safety
- `fmtlib <https://github.com/fmtlib/fmt>`_ (header-only): the proper design and implementation of a printf-like function according to C++ goals, since C++20 part of fmt is in the standard library header :cch:`<format>`
