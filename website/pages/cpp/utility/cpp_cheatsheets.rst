.. title: C++ cheatsheets
.. slug: cpp_cheatsheets
.. description: C++ cheatsheets
.. author: Xeverous

Operators and operator overloading
##################################

.. list-table::
    :header-rows: 1

    * - precendence
      - name
      - operator
      - arity
      - associativity
      - overloading
      - notes
    * - 1
      - scope resolution
      - ``a::b``, ``::a``
      - 1-2
      - LtR
      - \-
      -
    * - 2
      - suffix increment
      - ``a++``
      - 1
      - LtR
      - member
      -
    * - 2
      - suffix decrement
      - ``a--``
      - 1
      - LtR
      - member
      -
    * - 2
      - functional cast
      - ``T(a)``
      - 1
      - LtR
      - member
      -
    * - 2
      - functional cast
      - ``T{a}``
      - 1
      - LtR
      - member
      -
    * - 2
      - function call
      - ``a()``
      - 1+
      - LtR
      - member
      -
    * - 2
      - subscript
      - ``a[]``
      - 1+
      - LtR
      - member
      -
    * - 2
      - member access
      - ``a.b``
      - 1
      - LtR
      - \-
      -
    * - 2
      - member access
      - ``a->b``
      - 1
      - LtR
      - \-
      -
    * - 3
      - prefix increment
      - ``++a``
      - 1
      - RtL
      - member
      -
    * - 3
      - prefix decrement
      - ``--a``
      - 1
      - RtL
      - member
      -
    * - 3
      - unary plus
      - ``+a``
      - 1
      - RtL
      - member
      -
    * - 3
      - unary minus
      - ``-a``
      - 1
      - RtL
      - member
      -
    * - 3
      - logical NOT
      - ``!a``
      - 1
      - RtL
      - member
      -
    * - 3
      - bitwise NOT
      - ``~a``
      - 1
      - RtL
      - member
      -
    * - 3
      - C-style cast
      - ``(T) a``
      - 1
      - RtL
      - member
      -
    * - 3
      - dereference
      - ``*a``
      - 1
      - RtL
      - member
      -
    * - 3
      - address-of
      - ``&a``
      - 1
      - RtL
      - member
      - overloading discouraged
    * - 3
      - size-of
      - :cch:`sizeof T`, :cch:`sizeof a`
      - 1
      - RtL
      - \-
      -
    * - 3
      - await expression
      - :cch:`co_await a`
      - 1
      - RtL
      - member
      - C++20
    * - 3
      - dynamic memory allocation
      - :cch:`new`
      - 1+
      - RtL
      - free, member
      -
    * - 3
      - dynamic memory allocation
      - :cch:`new[]`
      - 1+
      - RtL
      - free, member
      -
    * - 3
      - dynamic memory deallocation
      - :cch:`delete`
      - 1
      - RtL
      - free, member
      -
    * - 3
      - dynamic memory deallocation
      - :cch:`delete[]`
      - 1
      - RtL
      - free, member
      -
    * - 4
      - pointer-to-member access
      - ``a.*b``
      - 1
      - LtR
      - \-
      -
    * - 4
      - pointer-to-member access
      - ``a->*b``
      - 1
      - LtR
      - member
      -
    * - 5
      - multiplication
      - ``a * b``
      - 2
      - LtR
      - recommended free
      -
    * - 5
      - division
      - ``a / b``
      - 2
      - LtR
      - recommended free
      -
    * - 5
      - remainer
      - ``a % b``
      - 2
      - LtR
      - recommended free
      -
    * - 6
      - addition
      - ``a + b``
      - 2
      - LtR
      - recommended free
      -
    * - 6
      - subtraction
      - ``a - b``
      - 2
      - LtR
      - recommended free
      -
    * - 7
      - bitwise left shift
      - ``a << b``
      - 2
      - LtR
      - recommended free
      -
    * - 7
      - bitwise right shift
      - ``a >> b``
      - 2
      - LtR
      - recommended free
      -
    * - 8
      - three-way comparison, spaceship
      - ``a <=> b``
      - 2
      - LtR
      - free, member
      - C++20
    * - 9
      - less than
      - ``a < b``
      - 2
      - LtR
      - recommended free
      -
    * - 9
      - less than or equal to
      - ``a <= b``
      - 2
      - LtR
      - recommended free
      -
    * - 9
      - greater than
      - ``a > b``
      - 2
      - LtR
      - recommended free
      -
    * - 9
      - greater than or equal to
      - ``a >= b``
      - 2
      - LtR
      - recommended free
      -
    * - 10
      - equal to
      - ``a == b``
      - 2
      - LtR
      - recommended free
      -
    * - 10
      - not equal to
      - ``a != b``
      - 2
      - LtR
      - recommended free
      -
    * - 11
      - bitwise AND
      - ``a & b``
      - 2
      - LtR
      - recommended free
      -
    * - 12
      - bitwise XOR
      - ``a ^ b``
      - 2
      - LtR
      - recommended free
      -
    * - 13
      - bitwise OR
      - ``a | b``
      - 2
      - LtR
      - recommended free
      -
    * - 14
      - logical AND
      - ``a && b``
      - 2
      - LtR
      - recommended free
      - overloads lose short-circuit evaluation
    * - 15
      - logical OR
      - ``a || b``
      - 2
      - LtR
      - recommended free
      - overloads lose short-circuit evaluation
    * - 16
      - ternary conditional
      - ``a ? b : c``
      - 3
      - RtL
      - \-
      -
    * - 16
      - throw
      - :cch:`throw`, :cch:`throw a`
      - 0-1
      - RtL
      - \-
      -
    * - 16
      - yield expression
      - :cch:`co_yield a`
      - 1
      - RtL
      - \-
      - C++20
    * - 16
      - direct assignment
      - ``a = b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by sum
      - ``a += b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by difference
      - ``a -= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by product
      - ``a *= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by quotient
      - ``a /= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by remainder
      - ``a %= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by bitwise left shift
      - ``a <<= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by bitwise right shift
      - ``a >>= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by bitwise AND
      - ``a &= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by bitwise XOR
      - ``a ^= b``
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by bitwise OR
      - ``a |= b``
      - 2
      - RtL
      - member
      -
    * - 17
      - comma
      - ``a, b``
      - 2
      - LtR
      - recommended free
      - overloading discouraged
    * - \-
      - user-defined literal
      - ``""a``
      - 1-2
      - \-
      - free
      -
    * - \-
      - static cast
      - :cch:`static_cast<T>(a)`
      - 1
      - \-
      - member
      - C++11
    * - \-
      - dynamic cast
      - :cch:`dynamic_cast<T>(a)`
      - 1
      - \-
      - \-
      - C++11
    * - \-
      - const cast
      - :cch:`const_cast<T>(a)`
      - 1
      - \-
      - \-
      - C++11
    * - \-
      - reinterpret cast
      - :cch:`reinterpret_cast<T>(a)`
      - 1
      - \-
      - \-
      - C++11
    * - \-
      - size-of parameter pack
      - :cch:`sizeof...(T)`, :cch:`sizeof...(a)`
      - 1
      - \-
      - \-
      - C++11
    * - \-
      - typeid
      - :cch:`typeid(T)`, :cch:`typeid(a)`
      - 1
      - \-
      - \-
      - C++11
    * - \-
      - noexcept
      - :cch:`noexcept(a)`
      - 1
      - \-
      - \-
      - C++11
    * - \-
      - alignof
      - :cch:`alignof(T)`, :cch:`alignof(a)`
      - 1
      - \-
      - \-
      - C++11

Notes:

- **precendence** - C++ has no formal precendence of operators. Their precendence is implicitly defined by the grammar. Operators with no precedence are never ambiguous.
- **arity** - number of operands (including :cch:`*this` if appropriate).
- **associativity**:

  - left-to-right: ``a @ b @ c`` is equivalent to ``(a @ b) @ c``
  - right-to-left: ``a @ b @ c`` is equivalent to ``a @ (b @ c)``

- **overloading**:

  - free - must be a free function
  - member - must be a member function
  - free, member - can be both free function and member function, no recommendation
  - recommended free - can be both a free function and a member function, recommended free function
  - \- - can not be overloaded

Initialization
##############

- https://josuttis.com/cpp/c++initialization.pdf
- http://randomcat.org/cpp_initialization/initialization.png
- http://randomcat.org/cpp_initialization/initialization.svg
