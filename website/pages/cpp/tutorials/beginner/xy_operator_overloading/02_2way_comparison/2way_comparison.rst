.. title: 02 - 2-way comparison
.. slug: index
.. description: 2-way comparison operators
.. author: Xeverous

.. TODO this lesson requires explanation of assert macro

We start with the simplest operators - ones which do not need to modify the object.

Equality
########

.. cch::
    :code_path: equality.cpp
    :color_path: equality.color

Notes:

- There is no requiremenet to return :cch:`bool`, but you need a really good reason to return an object of a different type (e.g. EDSL).
- By convention (to avoid code duplication):

  - :cch:`operator!=` is implemeted in terms of :cch:`operator==`.
  - :cch:`operator>` is implemeted in terms of :cch:`operator<`.
  - :cch:`operator<=` is implemeted in terms of :cch:`operator>`.
  - :cch:`operator>=` is implemeted in terms of :cch:`operator<`.

..

    Isn't this reuse (negating result of a different comparison) slower than manual implementation?

No, it is not. Compilers today do very advanced optimizations and they easily inline and remove redundant operations. There are also some hardware specific quirks (e.g. whether ``<`` takes less cycles than ``<=``) that they take into account.

Member overloads
################

.. admonition:: error
    :class: error

    Many C++ learning materials (and beginners) notoriously commit this mistake.

.. admonition:: tip
    :class: tip

    Commutative binary operators should be implemented as free functions.

Free function implementation has easier to read code but more importantly, it treats both arguments the same way. Member operator overloads do not, because **second operand can be implicitly converted while first not**.

.. cch::
    :code_path: member_overloads.cpp
    :color_path: member_overloads.color

The cause of this assymetry is the fact that if you call a member function, it's already known on what type of the object the function is called. The reverse situation - searching for member functions on a non-class type is not possible.

Thus, "symmetrical" (commutative binary) operators should be implemented as free functions.

Mixed-type comparisons
######################

Sometimes you might also want to compare 2 different types, usually one is a subset of another.

Example: a game where every player has unique ID:

.. cch::
    :code_path: player_id.cpp
    :color_path: player_id.color

Then you simply need to provide extra overloads:

.. cch::
    :code_path: player_id_extra_overloads.cpp
    :color_path: player_id_extra_overloads.color

The benefit of writing such extra operators is that if you have an ID and a player, you don't need to construct a temporary player object only to compare them. If object construction is expensive, this extra code improves performance. If multiple types share a common subobject that needs to be compared, the most resonable implementation would be to add :cch:`int get_id() const;$$$keyword func() keyword;` to every type.

:cch:`std::string`, :cch:`std::string_view` and :cch:`const char*` do not share a common member (each refers to a sequence of characters differently) so instead many operator overloads are present to support every combination.

There is no need to do such thing with the :cch:`fraction$$$type` class - we can rely on implicit construction from integers. Fraction is a very cheap type to construct and copy (it's just 2 integers) so there is no benefit in writing extra comparison operators. Very likely each comparison call is inlined and any temporary objects optimized out.

3-way helpers
#############

Sometimes you might already have a comparison helper in the form of a 2-argument function, which returns negative, zero or positive number depending on the ordering between elements - this style is very popular in C, including standard library functions :cch:`memcmp`, :cch:`strcmp`, :cch:`strncmp`. In such case, all comparison operators can use the helper:

.. cch::
    :code_path: 3way_helper.cpp
    :color_path: 3way_helper.color

Lexicographical comparison
##########################

If you have a type with multiple members and need to implement lexicographical comparison, you can use :cch:`std::tie` (which creates :cch:`std::tuple` of references) and rely on tuple's comparison operators:

.. cch::
    :code_path: tuple_comparison.cpp
    :color_path: tuple_comparison.color

Recommendation
##############

- Every type should either:

  - overload all 6 comparison operators
  - overload only :cch:`operator==` and :cch:`operator!=`
  - overload none of these

- For types that overload all operators:

  - *equivalence* (``!(a < b) && !(b < a)``) and *equality* (``a == b``) should always have the same result.
  - ``a <= b`` should always have the same result as ``a < b || a == b``.
