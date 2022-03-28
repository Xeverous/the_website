.. title: 03 - std::array
.. slug: index
.. description: standard library array type
.. author: Xeverous

By the time you are reading this you should understand:

- how arrays work (size and indexing)
- how to pass and use arrays in functions
- array limitations (no easy way to compare and copy)

The arrays presented so far are often called "raw arrays", "built-in arrays" or "C arrays". This is because they are one of fundamental parts of the C language, one which C++ inherited, including it's limitations and problematic language rules. Since majority of rules regarding arrays can not be changed (too much code breakage), C++11 added an alternative.

Originally :cch:`boost::array`, `std::array` is a wrapper type build on top of C arrays. It's core definition looks roughly like this:

.. cch::
    :code_path: std_array_pseudodef.cpp
    :color_path: std_array_pseudodef.color

The type syntax of this standard library type is slightly different because here the stored type and array size are specified as template parameters. **All typical operations have been defined to be very intuitive by reusing existing operators.** The specific feature in play here is *operator overloading* which allows to define meanings for operators for *user-defines types* so that they can be used just like built-in types. The feature is explained in its own chapter.

.. cch::
    :code_path: std_array_example.cpp
    :color_path: std_array_example.color

Main benefits of using :cch:`std::array` are:

- type safety - unline C arrays, this type does not *decay*
- support for common operations such as comparison and copying
- support for range-based loops and iterators
- additional *member functions* such as :cch:`.size()$$$.func()`

range-based loops
#################
