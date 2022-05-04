.. title: 08 - bit
.. slug: index
.. description: overloading bit operator
.. author: Xeverous

I can imagine only 2 kinds of types for which overloading bit operators makes sense:

- bit mask types
- types from an EDSL library

For bit mask types, overloads follow arithmetic overloads conventions, with the difference that compound versions are non-member (enumerations can not have member functions).

Below canonical implementation for a filesystem permissions bit mask enumeration (from `user-defined types / enum flags <link://filename/pages/cpp/tutorials/beginner/05_user_defined_types/03_enum_flags/enum_flags.rst>`_):

.. cch::
    :code_path: bit.cpp
    :color_path: bit.color
