.. title: 03 - std::array
.. slug: index
.. description: standard library array type
.. author: Xeverous

:cch:`std::array`
#################

Changing any such rules would be very risky (and also breaking backwards compatibility) so C++11 came up with a better alternative that has been defined mostly like this:

.. cch::
    :code_path: std_array_pseudodef.cpp
    :color_path: std_array_pseudodef.color

You likely won't get templates and most of the code from this example but to put it shortly - :cch:`std::array` is a wrapper type that has been defined on top of already existing arrays (sometimes called C-arrays to differentiate them from the standard library array type).

The type syntax of the standard library type is different due to templates, but **all other operations have been defined to be very intuitive and reuse existing operators**. The specific feature in play here is *operator overloading* and its core idea is to allow to reuse operators for custom types so that they can be used just like built-in types (e.g. :cch:`int`). The feature is explained in its own chapter.

.. cch::
    :code_path: std_array_example.cpp
    :color_path: std_array_example.color

Main benefits of using :cch:`std::array` are:

- type safety
- support for common operators
- additional *member functions*
- support for ranged-based loops and iterators

.. TODO where to actually explain ranged loops?
.. functions chapter should already cover const reference
