.. title: 01 - introduction
.. slug: 01_introduction
.. description: introduction to operator overloading
.. author: Xeverous

Operators like ``+``, ``-``, ``*``, ``/``, ``%`` (and many others) by default only work with built-in types. Operator overloading lets you define behaviour of operators for user-defined types (enumerations and classes). This feature allows to write very short and intuitive code.

C++ standard library has overloaded operators in many places (many of which you have already used):

- ``=``, ``==`` and ``!=`` for a huge number of types
- ``<<`` and ``>>`` for stream I/O
- ``+`` for strings
- ``*`` and ``->`` for smart pointers
- ``[]`` for multiple containers
- and many more

.. admonition:: note
    :class: note

    Even through this chapter is purely about operator overloading, it does not explain overloading of operators :cch:`new`, :cch:`new[]`, :cch:`delete` and :cch:`delete[]`. These require advanced C++ knowledge and this has been put in TODO link.

Restrictions
############

All of these restrictions aim to reduce potential surprises.

- These operators can not be overloaded: ``::``, ``.``, ``.*``, ``?:``.
- :cch:`operator->` must return a raw pointer or a type for which this operator is also overloaded.
- You can not create new operators - e.g. ``%%`` or ``<-``.
- You can not change arity of operators - if ``/`` takes 2 arguments normally, it must be a 2-argument function.
- Overloaded :cch:`operator&&` and :cch:`operator||` lose *short-circuit evaluation*.
- At least one of operands must be a user-defined type - you can't redefine behaviour for built-in types.
- You can not change operator precedence - overloaded :cch:`x + y * z$$$var_local + var_local * var_local` will always be treated as :cch:`x + (y * z)$$$var_local + (var_local * var_local)`, never as :cch:`(x + y) * z$$$(var_local + var_local) * var_local`.
- You can not change operator associativity:

  - (RtL operators) overloaded :cch:`x = y = z$$$var_local = var_local = var_local` will always be treated as :cch:`x = (y = z)$$$var_local = (var_local = var_local)`, never as :cch:`(x = y) = z$$$(var_local = var_local) = var_local`.
  - (LtR operators) overloaded :cch:`x << y << z$$$var_local << var_local << var_local` will always be treated as :cch:`(x << y) << z$$$(var_local << var_local) << var_local`, never as :cch:`x << (y << z)$$$var_local << (var_local << var_local)`.

Some operators must be member functions, some must be free functions and some can be both. More info and recommendation for each in specific lessons.

Syntax
######

Operators are just functions with special names. The name syntax is :cch:`operator` keyword followed by operator token. These functions can also be called directly by their name, not just as operators.

Recommendations
###############

- Unlike functions, operators don't have names so if they exist, it should be very clear what they do. Write their implementation so that it always preserves intuitive mathematical rules:

  - ``x == y`` should have the same result as ``y == x``
  - ``x != y`` should have the same result as ``!(x == y)``
  - ``(x + y) + z`` should have the same result as ``x + (y + z)``
  - ``x = x + y`` should have the same result as ``x += y``
  - after ``y = x``, ``y == x``
  - and so on...

- Don't overload ``&&``, ``||``, ``,`` and unary ``&``. They can easily slip into unexpected places and have very nasty consequences.
- Overloaded operators should be defined in the same namespace as one of their operand types (this isn't just for consistency, it has consequences in how overload resolution works). Remember that (by default) it's not allowed to place new entities in namespace :cch:`std` so if one of operands is a standard library type and the other is your type - write the overload in your type's namespace.

EDSL
####

There is one particular use of operator overloading that violates multiple recommendations, nonetheless it's very useful - EDSL (embedded domain specific language). The goal is to mimic a different language inside C++ through overloaded operators. A prime example of this is Boost.Spirit library, which uses overloaded operators to construct parsers that match specific grammars in arbitrary input:

.. TOCOLOR

.. code::

    // example using third edition of the library
    namespace x3 = boost::spirit::x3;

    // # followed by any number of (any character except end-of-line) followed by (end-of-line or end-of-input)
    const auto directive           = '#'  > *(x3::char_ - x3::eol) > (x3::eol | x3::eoi);

    const auto single_line_comment = "//" > *(x3::char_ - x3::eol) > (x3::eol | x3::eoi);
    const auto multi_line_comment  = "/*" > *(x3::char_ - "*/") > "*/";
    const auto comment = single_line_comment | multi_line_comment;

More information:

- https://en.wikipedia.org/wiki/Spirit_Parser_Framework (describes older second edition but gives a good overview)
- https://en.wikipedia.org/wiki/Domain-specific_language

..

    Is there a project where overloading :cch:`operator,` made sense?

Yes. C++ is a fun language where even the most obscure features will be found by someone to be useful. :cch:`operator,` is overloaded in `Boost.Assign <http://www.boost.org/doc/libs/release/libs/assign/doc/index.html#intro>`_ to extend interface of STL containers. This library is somewhat old (pre modern C++ era); since C++11 there are much better (and less confusing) ways to do things what the library provides.

Practice
########

In practice, very few classes have overloaded operators other than ``=``, ``==`` and ``!=`` or user-defined convertion. Thus, **you can skip this chapter and come back later. Vast majority of code does not need to overload any operators** so there is no significant value in trying to remember all possible recommendations for each operator mentioned in this chapter - **use this chapter more as a reference than lessons you have to go through**.
