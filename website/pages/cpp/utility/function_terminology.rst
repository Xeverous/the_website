.. title: function terminology
.. slug: function_terminology
.. description: arguments, parameters, signature, type, prototype
.. author: Xeverous

There is a lot of confusion in function terminology, some people use the terms interchangeably and don't even realize they aren't the same.

Arguments vs parameters
#######################

- Parameters: what the function expects (as seen from the inside).
- Arguments: what the function is given (as seen from the outside).

Thus:

- There is *default arguments* feature, not *default parameters*.
- Compilers may print an error that a given argument does not match specific parameter.

Type vs prototype vs signature
##############################

Briefly:

- Signature: information which differentiates the function from others when overloading.
- Type: Every object and function has a type. The most significant application are function pointers.
- Prototype: Types of arguments (for compiler checks). C (until C23) allows to declare functions without prototype (empty parenthesis or old-style K&R syntax). In C, calling a function without prototype disables compile time checks and will invoke undefined behavior if the number of arguments doesn't match the number of parameters. In C++ it's not possible to declare a function without prototype. In C it's a common compiler setting to enable warnings on functions with missing prototype.

.. list-table::
  :header-rows: 1

  * -
    - signature
    - type
    - prototype
  * - amount and types of parameters
    - |tick|
    - |tick|
    - |tick|
  * - return type
    -
    - |tick|
    -
  * - exception specification
    -
    - since C++17
    -
  * - member function qualifiers
    - |tick|
    - |tick|
    -
  * - (since C++11) attributes
    -
    - |tick|
    -
  * - (since C++20) concept constraints
    - |tick|
    -
    -

.. |tick| unicode:: 0x2714

Prior to C++17, exception specification wasn't a part of function type. It was added to facilitate type system in more contexts - most notably now a function pointer can express it accepts only :cch:`noexcept` functions.
