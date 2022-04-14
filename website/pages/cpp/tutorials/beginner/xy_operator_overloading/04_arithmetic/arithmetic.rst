.. title: 04 - arithmetic
.. slug: index
.. description: arithmetic operators
.. author: Xeverous

Binary arithmetic operators
###########################

These should be very intuitive.

.. cch::
    :code_path: binary_arithmetic.cpp
    :color_path: binary_arithmetic.color

There are no special requirements on these operators, but for any typical implementation of overloads:

- they return by value
- they take parameters by value or const reference (here by value is used because the type is very cheap to copy)

Anything else simply doesn't make any sense.

Unary arithmetic operators
##########################

You might already used unary minus in expressions like :cch:`x = -x`. Unary plus isn't very useful (it does not modify value for built-in integer and floating-point types) but exists for consistency. Unary plus is used in more arcane applications of operator overloading such as EDSLs.

Unary plus and unary minus can be overloaded both as free functions and as member functions. There is no recommendation here - even the standard library is not consistent: :cch:`std::complex` uses non-member overloads and :cch:`std::chrono::duration` uses member overloads.

.. TODO *this explanation when?

.. cch::
    :code_path: unary_arithmetic.cpp
    :color_path: unary_arithmetic.color

.. cch::
    :code_path: assertions.cpp
    :color_path: assertions.color

..

    Is there any semantic difference between member and non-member unary operator overloads?

Yes. Just like with binary operators, member overloads do not allow implicit convertions for the first argument. Below is an example that allows you to test it - uncomment any of 2 functions and try compiling. I had to create 2 types because built-in types already have these operators defined so the only case where the implicit convertion can be used is between 2 user-defined types.

.. cch::
    :code_path: semantic_difference.cpp
    :color_path: semantic_difference.color
