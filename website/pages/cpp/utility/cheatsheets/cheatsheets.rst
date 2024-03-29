.. title: cheatsheets
.. slug: index
.. description: C++ cheatsheets
.. author: Xeverous

.. details::
  :summary: Operators and operator overloading

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
        - ``x::y``, ``::x``
        - 1-2
        - LtR
        - \-
        -
      * - 2
        - suffix increment
        - :cch:`x++`
        - 1
        - LtR
        - member
        -
      * - 2
        - suffix decrement
        - :cch:`x--`
        - 1
        - LtR
        - member
        -
      * - 2
        - functional cast
        - :cch:`T(x)$$$param_tmpl(var_local)`
        - 1
        - LtR
        - member
        -
      * - 2
        - functional cast
        - :cch:`T{x}$$$param_tmpl{var_local}`
        - 1
        - LtR
        - member
        - C++11
      * - 2
        - function call
        - :cch:`x()$$$var_local()`
        - 1+
        - LtR
        - member
        -
      * - 2
        - subscript
        - :cch:`x[]`
        - 2
        - LtR
        - member
        -
      * - 2
        - member access
        - :cch:`x.y`
        - 1
        - LtR
        - \-
        -
      * - 2
        - member access
        - :cch:`x->y`
        - 1
        - LtR
        - member
        - has return type restrictions
      * - 3
        - prefix increment
        - :cch:`++x`
        - 1
        - RtL
        - member
        -
      * - 3
        - prefix decrement
        - :cch:`--x`
        - 1
        - RtL
        - member
        -
      * - 3
        - unary plus
        - :cch:`+x`
        - 1
        - RtL
        - both
        -
      * - 3
        - unary minus
        - :cch:`-x`
        - 1
        - RtL
        - both
        -
      * - 3
        - logical NOT
        - :cch:`!x`
        - 1
        - RtL
        - member
        -
      * - 3
        - bitwise NOT
        - :cch:`~x`
        - 1
        - RtL
        - member
        -
      * - 3
        - C-style cast
        - :cch:`(T) x$$$(param_tmpl) var_local`
        - 1
        - RtL
        - member
        -
      * - 3
        - dereference
        - :cch:`*x`
        - 1
        - RtL
        - member
        -
      * - 3
        - address-of
        - :cch:`&x`
        - 1
        - RtL
        - member
        - overloading discouraged
      * - 3
        - size-of
        - :cch:`sizeof T`, :cch:`sizeof x$$$keyword var_local`
        - 1
        - RtL
        - \-
        -
      * - 3
        - await expression
        - :cch:`co_await x$$$keyword var_local`
        - 1
        - RtL
        - member
        - C++20
      * - 3
        - dynamic memory allocation
        - :cch:`new`
        - 1+
        - RtL
        - both
        -
      * - 3
        - dynamic memory allocation
        - :cch:`new[]`
        - 1+
        - RtL
        - both
        -
      * - 3
        - dynamic memory deallocation
        - :cch:`delete`
        - 1
        - RtL
        - both
        -
      * - 3
        - dynamic memory deallocation
        - :cch:`delete[]`
        - 1
        - RtL
        - both
        -
      * - 4
        - pointer-to-member access
        - :cch:`x.*y`
        - 1
        - LtR
        - \-
        -
      * - 4
        - pointer-to-member access
        - :cch:`x->*y`
        - 1
        - LtR
        - member
        -
      * - 5
        - multiplication
        - :cch:`x * y`
        - 2
        - LtR
        - recommended free
        -
      * - 5
        - division
        - :cch:`x / y`
        - 2
        - LtR
        - recommended free
        -
      * - 5
        - remainer
        - :cch:`x % y`
        - 2
        - LtR
        - recommended free
        -
      * - 6
        - addition
        - :cch:`x + y`
        - 2
        - LtR
        - recommended free
        -
      * - 6
        - subtraction
        - :cch:`x - y`
        - 2
        - LtR
        - recommended free
        -
      * - 7
        - bitwise left shift
        - :cch:`x << y`
        - 2
        - LtR
        - recommended free
        -
      * - 7
        - bitwise right shift
        - :cch:`x >> y`
        - 2
        - LtR
        - recommended free
        -
      * - 8
        - three-way comparison, spaceship
        - :cch:`x <=> y`
        - 2
        - LtR
        - both
        - C++20
      * - 9
        - less than
        - :cch:`x < y`
        - 2
        - LtR
        - recommended free
        -
      * - 9
        - less than or equal to
        - :cch:`x <= y`
        - 2
        - LtR
        - recommended free
        -
      * - 9
        - greater than
        - :cch:`x > y`
        - 2
        - LtR
        - recommended free
        -
      * - 9
        - greater than or equal to
        - :cch:`x >= y`
        - 2
        - LtR
        - recommended free
        -
      * - 10
        - equal to
        - :cch:`x == y`
        - 2
        - LtR
        - recommended free
        -
      * - 10
        - not equal to
        - :cch:`x != y`
        - 2
        - LtR
        - recommended free
        -
      * - 11
        - bitwise AND
        - :cch:`x & y`
        - 2
        - LtR
        - recommended free
        -
      * - 12
        - bitwise XOR
        - :cch:`x ^ y`
        - 2
        - LtR
        - recommended free
        -
      * - 13
        - bitwise OR
        - :cch:`x | y`
        - 2
        - LtR
        - recommended free
        -
      * - 14
        - logical AND
        - :cch:`x && y`
        - 2
        - LtR
        - recommended free
        - overloads lose short-circuit evaluation
      * - 15
        - logical OR
        - :cch:`x || y`
        - 2
        - LtR
        - recommended free
        - overloads lose short-circuit evaluation
      * - 16
        - ternary conditional
        - :cch:`x ? y : z$$$var_local ? var_local : var_local`
        - 3
        - RtL
        - \-
        -
      * - 16
        - throw
        - :cch:`throw`, :cch:`throw x$$$keyword var_local`
        - 0-1
        - RtL
        - \-
        -
      * - 16
        - yield expression
        - :cch:`co_yield x$$$keyword var_local`
        - 1
        - RtL
        - \-
        - C++20
      * - 16
        - direct assignment
        - :cch:`x = y`
        - 2
        - RtL
        - member
        -
      * - 16
        - compound assignment by sum
        - :cch:`x += y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by difference
        - :cch:`x -= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by product
        - :cch:`x *= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by quotient
        - :cch:`x /= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by remainder
        - :cch:`x %= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by bitwise left shift
        - :cch:`x <<= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by bitwise right shift
        - :cch:`x >>= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by bitwise AND
        - :cch:`x &= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by bitwise XOR
        - :cch:`x ^= y`
        - 2
        - RtL
        - recommended member
        -
      * - 16
        - compound assignment by bitwise OR
        - :cch:`x |= y`
        - 2
        - RtL
        - recommended member
        -
      * - 17
        - comma
        - :cch:`x, y`
        - 2
        - LtR
        - recommended free
        - overloading discouraged
      * - \-
        - user-defined literal
        - :cch:`""x$$$str1suf`
        - 1
        - \-
        - free
        - C++11
      * - \-
        - static cast
        - :cch:`static_cast<T>(x)$$$keyword<param_tmpl>(var_local)`
        - 1
        - \-
        - member
        - C++11
      * - \-
        - dynamic cast
        - :cch:`dynamic_cast<T>(x)$$$keyword<param_tmpl>(var_local)`
        - 1
        - \-
        - \-
        - C++11
      * - \-
        - const cast
        - :cch:`const_cast<T>(x)$$$keyword<param_tmpl>(var_local)`
        - 1
        - \-
        - \-
        - C++11
      * - \-
        - reinterpret cast
        - :cch:`reinterpret_cast<T>(x)$$$keyword<param_tmpl>(var_local)`
        - 1
        - \-
        - \-
        - C++11
      * - \-
        - size-of parameter pack
        - :cch:`sizeof...(T)`, :cch:`sizeof...(x)$$$keyword...(var_local)`
        - 1
        - \-
        - \-
        - C++11
      * - \-
        - typeid
        - :cch:`typeid(T)`, :cch:`typeid(x)$$$keyword(var_local)`
        - 1
        - \-
        - \-
        - C++11
      * - \-
        - noexcept
        - :cch:`noexcept(x)$$$keyword(var_local)`
        - 1
        - \-
        - \-
        - C++11
      * - \-
        - alignof
        - :cch:`alignof(T)`, :cch:`alignof(x)$$$keyword(var_local)`
        - 1
        - \-
        - \-
        - C++11

  Legend:

  - **precendence** - C++ has no formal precendence of operators. Their precendence is implicitly defined by the grammar.

    - If multiple operators have the same precedence they are applied according to their associativity.
    - Operators with no precedence in the table are never ambiguous.

  - **arity** - number of operands (including :cch:`*this` if appropriate). In cases like ``x.y`` and ``x->y`` the arity is 1 because ``y`` does not contribute to the operator's output.
  - **associativity**:

    - left-to-right: ``x @ y @ z`` is equivalent to ``(x @ y) @ z``
    - right-to-left: ``x @ y @ z`` is equivalent to ``x @ (y @ z)``

  - **overloading**:

    - free - must be a free function
    - member - must be a member function
    - both - can be both free function and member function, no recommendation
    - recommended free - can be both a free function and a member function, recommended free function
    - recommended member - can be both a free function and a member function, recommended member function
    - \- - can not be overloaded

  Notes:

  - Overloading convertion operator affects all functional casts, C-style cast and :cch:`static_cast`.

.. details::
  :summary: RAII - canonical rule of 5 implementations

  Below are idiomatic implementations of classes that implement the *Rule of 5*.

  .. cch::
    :code_path: rule_of_5.cpp

  Depending on the class exact planned behavior (some may not have default constructor and default member initializers), a canonical implementation can replace swaps with member initializer lists using :cch:`std::exchange`:

  .. cch::
    :code_path: move_ctor_exchange.cpp
    :color_path: move_ctor_exchange.color

.. details::
  :summary: Initialization

  - meme summary: https://i.imgur.com/3wlxtI0.gifv
  - rules cheatsheets:

    - https://josuttis.com/cpp/c++initialization.pdf
    - https://twitter.com/timur_audio/status/1119160309573242880?s=21

  - actual specification cheatsheets:

    - http://randomcat.org/cpp_initialization/initialization.png
    - http://randomcat.org/cpp_initialization/initialization.svg
