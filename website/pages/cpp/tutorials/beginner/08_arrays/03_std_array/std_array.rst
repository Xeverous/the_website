.. title: 03 - std::array
.. slug: index
.. description: standard library array type
.. author: Xeverous

.. TODO this lesson seems too technical, probably too much details
.. TODO this lesson duplicates "sarr" struct example

By the time you are reading this you should understand:

- how arrays work (size and indexing)
- how to pass and use arrays in functions
- array limitations (no easy way to compare and copy)

The arrays presented so far are often called "raw arrays", "built-in arrays" or "C arrays". This is because they are one of fundamental parts of the C language, one which C++ inherited, including it's limitations. Since majority of rules regarding arrays can not be changed (too much code breakage), C++11 added an alternative.

Originally developed as :cch:`boost::array`, :cch:`std::array` is a wrapper type build on top of C arrays. It's core definition looks roughly like this:

.. cch::
    :code_path: std_array_pseudodef.cpp
    :color_path: std_array_pseudodef.color

The type syntax of this standard library type is different from C arrays because here the stored type and array size are specified as template parameters. **All typical operations have been defined to be very intuitive by reusing existing operators.** The specific feature in play here is *operator overloading* which allows to define meanings for operators for *user-defines types* so that they can be used just like built-in types. The feature is explained in its own chapter.

.. cch::
    :code_path: std_array_example.cpp
    :color_path: std_array_example.color

Main benefits of using :cch:`std::array` are:

- type safety - unline C arrays, this type does not *decay*
- support for common operations such as comparison and copying - *overloaded operators* are defined as functions which perform these tasks
- support for range-based loops and *iterators*
- additional *member functions* such as :cch:`.size()$$$.func()`

Range-based loops
#################

C++11 introduced syntax sugar that was already common in the programming world. Better known as *for-each loops* (*range-based loops* is strictly C++ terminology), it allows to write simplest loops in a shortened way.

The syntax is:

.. I know cppreference also lists *attr* grammar but attributes can be applied pretty much everywhere so listing them all the time is verbose - better just write about them in a separate lesson dedicated to attributes

.. cch::
    :code_path: range_based_loop_syntax.cpp
    :color_path: range_based_loop_syntax.color

This is strictly syntax sugar - it doesn't rely on any particular magic feature of arrays, ranged-based loops are rewritten by the compiler to act as if they were the following (magic variable names for the sake of example):

.. cch::
    :code_path: range_based_loop_expanded.cpp
    :color_path: range_based_loop_expanded.color

- if :cch:`range-expression$$$0spec` is a C-array:

  - :cch:`begin_expr$$$spec` is :cch:`__range$$$var_local`
  - :cch:`end_expr$$$spec` is :cch:`__range + __array_size$$$var_local + var_local` where :cch:`__array_size$$$var_local` is the size of the array

- else if :cch:`range-expression$$$0spec` is a class type that has members named ``begin`` and ``end``:

  - :cch:`begin_expr$$$spec` is :cch:`__range.begin()$$$var_local.func()`
  - :cch:`end_expr$$$spec` is :cch:`__range.end()$$$var_local.func()`

- else:

  - :cch:`begin_expr$$$spec` is :cch:`begin(__range)$$$func(var_local)`
  - :cch:`end_expr$$$spec` is :cch:`end(__range)$$$func(var_local)`

Don't worry if you don't get all this code - the whole feature exists so that you don't have to know all the details.

In other words, the variables used in the loop are initialized to:

- memory address range if the type is a C-array
- result of :cch:`begin()` and :cch:`end()` if the type has such member functions
- result of global functions otherwise (functions are expected to match range as their argument) (functions found by *ADL*) - this specific variant allows to write helper functions to iterate on foreign types (usually from an external library) when the type can not be modified (it's not your code)

.. TODO where/when to explain ADL?

Some examples to demonstrate:

.. cch::
    :code_path: range_based_loop_demo.cpp
    :color_path: range_based_loop_demo.color

..

    Can I loop backward using this syntax?

No. The shortest way would be to use *reverse iterators*, from :cch:`rbegin()` and :cch:`rend()`. There is no syntax sugar for these, so you would have to manually write the loop.

.. admonition:: tip
  :class: tip

  Use range-based loops whenever you are iterating in ascending index order and don't actually need the index value.

Range-based loops shorten code and eliminate possible errors caused by various mistakes with :cch:`i` and similar variables.

Array size
##########

For C arrays I have mentioned that they must have a positive size (with the special case of 0 allowed by compiler extensions). :cch:`std::array` can have size 0 and will work just as expected:

- :cch:`.size()$$$.func()` will return 0
- :cch:`.begin()$$$.func()` will be :cch:`==` to :cch:`.end()$$$.func()`
- any loop will terminate immediately (no iterations would be made)

    How does is this possible if :cch:`std::array` contains a C-array inside? Are they implemented with compiler extensions?

No. They are implemented using *template specialization* which allows to provide separate definition for specific parameters. If the size parameter is 0, the definition is different. The main purpose of this specialization is to make it work consistently for any size parameter, even though size 0 has almost no practical value (but someone writing templates can accidentally create such arrays, without easily realizing it).

    How about negative size?

:cch:`std::array` template parameter for size has type :cch:`std::size_t` so it's not possible. If you write a negative value it will be converted to an unsigned type, likely resulting in a huge value because of how signed-to-unsigned convertion works (modulo 2 arithmetic).

Passing :cch:`std::array`
#########################

:cch:`std::array` does not *decay* so you can write functions which accept is as a parameter, but it's quite limiting in other way - the function will accept arrays of only certain size (template parameters are a part of type information).

Thus, it's recommended to still use:

- pointer + size: :cch:`(const T*, size_t)$$$(keyword tparam*, type)`
- (C++20) :cch:`(std::span<T>)$$$(namespace::type<tparam>)` which essentially is a struct containing pointer and size

Functions with such parameters will work for:

- C-arrays
- :cch:`std::array`
- :cch:`std::vector` and any other container (not necessarily from standard library) that has *contiguous storage*

..

    How do you pass :cch:`std::array` into a function? How to turn it to :cch:`const T*`?

:cch:`f(arr.data(), arr.size())$$$func(var_local.func(), var_local.func())`. This is the same for any *container* that follows standard library conventions. Different containers implement different *data structures* in memory, so each offers only a specific subset of all container-typical functions, but if a function of specific name is present, you can expect it to be usable in the same way.

Exercise
########

Take the code from previous exercise and rewrite C-arrays to :cch:`std::array`.
