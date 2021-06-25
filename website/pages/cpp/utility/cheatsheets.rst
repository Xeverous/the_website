.. title: cheatsheets
.. slug: cheatsheets
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
      - :cch:`a++`
      - 1
      - LtR
      - member
      -
    * - 2
      - suffix decrement
      - :cch:`a--`
      - 1
      - LtR
      - member
      -
    * - 2
      - functional cast
      - :cch:`T(a)`
      - 1
      - LtR
      - member
      -
    * - 2
      - functional cast
      - :cch:`T{a}`
      - 1
      - LtR
      - member
      - C++11
    * - 2
      - function call
      - :cch:`a()`
      - 1+
      - LtR
      - member
      -
    * - 2
      - subscript
      - :cch:`a[]`
      - 2
      - LtR
      - member
      -
    * - 2
      - member access
      - :cch:`a.b`
      - 1
      - LtR
      - \-
      -
    * - 2
      - member access
      - :cch:`a->b`
      - 1
      - LtR
      - member
      - has return type restrictions
    * - 3
      - prefix increment
      - :cch:`++a`
      - 1
      - RtL
      - member
      -
    * - 3
      - prefix decrement
      - :cch:`--a`
      - 1
      - RtL
      - member
      -
    * - 3
      - unary plus
      - :cch:`+a`
      - 1
      - RtL
      - free, member
      -
    * - 3
      - unary minus
      - :cch:`-a`
      - 1
      - RtL
      - free, member
      -
    * - 3
      - logical NOT
      - :cch:`!a`
      - 1
      - RtL
      - member
      -
    * - 3
      - bitwise NOT
      - :cch:`~a`
      - 1
      - RtL
      - member
      -
    * - 3
      - C-style cast
      - :cch:`(T) a`
      - 1
      - RtL
      - member
      -
    * - 3
      - dereference
      - :cch:`*a`
      - 1
      - RtL
      - member
      -
    * - 3
      - address-of
      - :cch:`&a`
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
      - :cch:`a.*b`
      - 1
      - LtR
      - \-
      -
    * - 4
      - pointer-to-member access
      - :cch:`a->*b`
      - 1
      - LtR
      - member
      -
    * - 5
      - multiplication
      - :cch:`a * b`
      - 2
      - LtR
      - recommended free
      -
    * - 5
      - division
      - :cch:`a / b`
      - 2
      - LtR
      - recommended free
      -
    * - 5
      - remainer
      - :cch:`a % b`
      - 2
      - LtR
      - recommended free
      -
    * - 6
      - addition
      - :cch:`a + b`
      - 2
      - LtR
      - recommended free
      -
    * - 6
      - subtraction
      - :cch:`a - b`
      - 2
      - LtR
      - recommended free
      -
    * - 7
      - bitwise left shift
      - :cch:`a << b`
      - 2
      - LtR
      - recommended free
      -
    * - 7
      - bitwise right shift
      - :cch:`a >> b`
      - 2
      - LtR
      - recommended free
      -
    * - 8
      - three-way comparison, spaceship
      - :cch:`a <=> b`
      - 2
      - LtR
      - free, member
      - C++20
    * - 9
      - less than
      - :cch:`a < b`
      - 2
      - LtR
      - recommended free
      -
    * - 9
      - less than or equal to
      - :cch:`a <= b`
      - 2
      - LtR
      - recommended free
      -
    * - 9
      - greater than
      - :cch:`a > b`
      - 2
      - LtR
      - recommended free
      -
    * - 9
      - greater than or equal to
      - :cch:`a >= b`
      - 2
      - LtR
      - recommended free
      -
    * - 10
      - equal to
      - :cch:`a == b`
      - 2
      - LtR
      - recommended free
      -
    * - 10
      - not equal to
      - :cch:`a != b`
      - 2
      - LtR
      - recommended free
      -
    * - 11
      - bitwise AND
      - :cch:`a & b`
      - 2
      - LtR
      - recommended free
      -
    * - 12
      - bitwise XOR
      - :cch:`a ^ b`
      - 2
      - LtR
      - recommended free
      -
    * - 13
      - bitwise OR
      - :cch:`a | b`
      - 2
      - LtR
      - recommended free
      -
    * - 14
      - logical AND
      - :cch:`a && b`
      - 2
      - LtR
      - recommended free
      - overloads lose short-circuit evaluation
    * - 15
      - logical OR
      - :cch:`a || b`
      - 2
      - LtR
      - recommended free
      - overloads lose short-circuit evaluation
    * - 16
      - ternary conditional
      - :cch:`a ? b : c`
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
      - :cch:`a = b`
      - 2
      - RtL
      - member
      -
    * - 16
      - compound assignment by sum
      - :cch:`a += b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by difference
      - :cch:`a -= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by product
      - :cch:`a *= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by quotient
      - :cch:`a /= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by remainder
      - :cch:`a %= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by bitwise left shift
      - :cch:`a <<= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by bitwise right shift
      - :cch:`a >>= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by bitwise AND
      - :cch:`a &= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by bitwise XOR
      - :cch:`a ^= b`
      - 2
      - RtL
      - recommended member
      -
    * - 16
      - compound assignment by bitwise OR
      - :cch:`a |= b`
      - 2
      - RtL
      - recommended member
      -
    * - 17
      - comma
      - :cch:`a, b`
      - 2
      - LtR
      - recommended free
      - overloading discouraged
    * - \-
      - user-defined literal
      - :cch:`""a`
      - 1
      - \-
      - free
      - C++11
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

Legend:

- **precendence** - C++ has no formal precendence of operators. Their precendence is implicitly defined by the grammar.
  - If multiple operators have the same precedence they are applied according to their associativity.
  - Operators with no precedence in the table are never ambiguous.
- **arity** - number of operands (including :cch:`*this` if appropriate). In cases like ``a.b`` and ``a->b`` the arity is 1 because ``b`` does not contribute to the operator's output.
- **associativity**:

  - left-to-right: ``a @ b @ c`` is equivalent to ``(a @ b) @ c``
  - right-to-left: ``a @ b @ c`` is equivalent to ``a @ (b @ c)``

- **overloading**:

  - free - must be a free function
  - member - must be a member function
  - free, member - can be both free function and member function, no recommendation
  - recommended free - can be both a free function and a member function, recommended free function
  - recommended member - can be both a free function and a member function, recommended member function
  - \- - can not be overloaded

Notes:

- Overloading convertion operator affects all functional casts, C-style cast and :cch:`static_cast`.

Initialization
##############

- https://josuttis.com/cpp/c++initialization.pdf
- http://randomcat.org/cpp_initialization/initialization.png
- http://randomcat.org/cpp_initialization/initialization.svg
