.. title: 01 - introduction
.. slug: index
.. description: introduction to operator overloading
.. author: Xeverous

Operators like ``+``, ``-``, ``*``, ``/``, ``%`` (and many others) by default only work with built-in types. Operator overloading lets you define behaviour of operators for user-defined types (enumerations and classes). This feature allows to write very short and intuitive code.

C++ standard library has overloaded operators in many places (many of which you have already used):

- ``=``, ``==`` and ``!=`` for a huge number of types
- ``<<`` and ``>>`` for stream I/O
- ``+`` for strings
- ``*`` and ``->`` for smart pointers
- ``[]`` for some containers
- and many more

.. admonition:: note
  :class: note

  Even through this chapter is purely about operator overloading, it does not explain overloading of all operators.

  - operators :cch:`new`, :cch:`new[]`, :cch:`delete` and :cch:`delete[]` are explained in seprate tutorial TOWRITE.
  - :cch:`operator=` is explained in RAII chapter TOWRITE.

TODO:

- ``->*``, ``->`` (???), also mention that :cch:`operator->` must return a raw pointer or a type (by value or by reference) for which this operator is also overloaded. This is because :cch:`a->b$$$var_local->var_member` is a shortcut for :cch:`(*a).b$$$(*var_local).var_member` which requires an object
- ``()``, ``[]`` (need good examples, possibly with STL)
- :cch:`co_await` (???)

Restrictions
############

All of these restrictions aim to reduce potential surprises.

- These operators can not be overloaded: ``::``, ``.``, ``.*``, ``?:``. Apart from (de)allocation functions, the only overloadable keyword operator is :cch:`co_await`.
- You can not create new operators - e.g. ``%%`` or ``<-``.
- You can not change arity of operators - if ``/`` takes 2 arguments normally, it must be a 2-argument function.
- Overloaded :cch:`operator&&` and :cch:`operator||` lose *short-circuit evaluation*.
- At least one of operands must be a user-defined type - you can't redefine behaviour for built-in types.
- You can not change operator precedence - overloaded :cch:`x + y * z$$$var_local + var_local * var_local` will always be treated as :cch:`x + (y * z)$$$var_local 1oo (var_local 1oo var_local)`, never as :cch:`(x + y) * z$$$(var_local 1oo var_local) 1oo var_local`.
- You can not change operator associativity:

  - (RtL operators) overloaded :cch:`x = y = z$$$var_local = var_local = var_local` will always be treated as :cch:`x = (y = z)$$$var_local 1oo (var_local 1oo var_local)`, never as :cch:`(x = y) = z$$$(var_local 1oo var_local) 1oo var_local`.
  - (LtR operators) overloaded :cch:`x << y << z$$$var_local << var_local << var_local` will always be treated as :cch:`(x << y) << z$$$(var_local 2oo var_local) 2oo var_local`, never as :cch:`x << (y << z)$$$var_local 2oo (var_local 2oo var_local)`.

Some operators must be member functions, some must be free functions and some can be both. Majority can not have default parameters (there is no syntax support). More info and recommendation for each in specific lessons.

.. cppreference: (untill C++17) &&, ||, and , (comma) lose their special sequencing properties when overloaded and behave like regular function calls even when they are used without function-call notation.
.. TODO I don't know what it means (apparently it's not short-circuit evaluation?) and have no example

Syntax
######

Operators are just functions with special names. The name syntax is :cch:`operator` keyword followed by operator token. These functions can also be called directly by their name, not just as operators.

Recommendations
###############

- Unlike functions, operators don't have names so if they exist, it should be very clear what they do. Write their implementation so that it preserves what is expected:

  - ``x == y`` should have the same result as ``y == x``
  - ``x != y`` should have the same result as ``!(x == y)``
  - ``(x + y) + z`` should have the same result as ``x + (y + z)``
  - ``x = x + y`` should have the same result as ``x += y``
  - after ``y = x``, ``y == x``
  - and so on...

- Don't overload ``&&``, ``||``, ``,`` and unary ``&``. They can easily slip into unexpected places and have very nasty consequences. Even EDSLs don't use them often.
- Overloaded operators should be defined in the same namespace as one of their operand types (this isn't just for consistency, it has consequences in how overload resolution works). Remember that (by default) it's not allowed to place new entities in namespace :cch:`std` so if one of operands is a standard library type and the other is your type - write the overload in your type's namespace (if the type is defined outside any namespace so should the operator).

EDSL
####

There is one particular use of operator overloading that violates multiple recommendations, nonetheless it's very useful - EDSL (embedded domain specific language). The goal is to mimic a different language inside C++ through overloaded operators. A prime example of this is Boost.Spirit library, which uses overloaded operators to construct parsers that match specific grammars in arbitrary input:

.. cch::
    :code_path: boost_spirit_example.cpp
    :color_path: boost_spirit_example.color

More information:

- https://en.wikipedia.org/wiki/Spirit_Parser_Framework (describes older second edition but gives a good overview)
- https://en.wikipedia.org/wiki/Domain-specific_language

..

    Is there a project where overloading :cch:`operator,` made sense?

Yes. C++ is a fun language where even the most obscure features will be found by someone to be useful. :cch:`operator,` is overloaded in `Boost.Assign <http://www.boost.org/doc/libs/release/libs/assign/doc/index.html#intro>`_ to extend interface of STL containers. This library is somewhat old (pre modern C++ era); since C++11 there are much better (and less confusing) ways to do things what the library provides.

In practice
###########

In practice, very few classes have overloaded operators other than ``=``, ``==`` and ``!=`` or user-defined convertion. **Majority of code does not need to overload any operators** so there is no significant value in trying to remember all possible recommendations for each operator mentioned in this chapter - **use this chapter more as a reference than lessons you have to go through**. If you want, skip all lessons except comparisons and user-defined convertion.
