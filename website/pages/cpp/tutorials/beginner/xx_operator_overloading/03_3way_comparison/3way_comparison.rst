.. title: 03 - 3-way comparison
.. slug: index
.. description: 3-way comparison operators
.. author: Xeverous

.. admonition:: note
    :class: note

    Everything described in this lesson was introduced in C++20.

.. admonition:: tip
    :class: tip

    If you don't have C++20 or don't want to write code which depends on these features, you can skip this lesson.

Rewritten candidates
####################

C++20 has made overload resolution smarter for comparison operators with the feature of *rewritten candidates* - if :cch:`x != y` is not valid, compiler will try :cch:`!(x == y)` and analogically for other comparison operators. Rewritten candidates are considered for both member and non-member overloads.

Thus:

- The guideline to implement comparison operators as non-members is no longer needed.
- You no longer need to implement so many operator overloads. The boilerplate work is now done by the compiler.
- Some compiler errors have been improved.

..

    Do *rewritten candidates* break existing special usages of operator overloading such as EDSL?

No. They are only considered if no implementation has been explicitly provided for remaining combinations.

Defaulted implementation
########################

Another improvement is that you can now :cch:`= default` all comparison operators if they are member functions. They will compare class members in order of their appearance (identical to :cch:`std::tie` trick from previous lesson).

The spaceship operator
######################

:cch:`operator<=>` represents 3-way comparison. It provides more information so a :cch:`bool` return type is not enough for it.

Before delving into what should be used instead of :cch:`bool`, you should first understand logical concepts that motivated multiple choices for the return type.

    Can I call ``<=>`` a TIE Fighter?

No. I have been informed that:

- TIE Fighter is ``|=|``
- ``<=>`` is Darth Vader's TIE Fighter
- ``<==>`` is TIE Bomber
- ``(=)`` is Inquisitor's TIE Advanced Prototype

Theory
######

Equality
========

There are 2 categories of equality:

- **strong equality** - if ``x == y``, objects are indistinguishable
- **weak equality** - even if ``x == y``, objects may differ

Examples:

- Integers have strong equality. Two integers which compare equal are exactly the same.
- Absolute value of integers has weak equality. Two integers can have equal absoule value (e.g. ``3`` and ``-3``) but they are distinguishable.
- Case-insensitive strings have weak equality. ``"abc"`` will compare equal to ``"ABC"``, but they are distinguishable.
- Comparing players by their score has weak equality - 2 players can compare equal due to the same score, but they are 2 different players.

In short, *weak equality* means that in a given scenario different objects may be given the same ranking (player score, case-insensitive strings) but the objects themselves are distinct (players reached the same score through different means, strings have letters with different case).

Ordering
========

There are 3 categories of ordering:

- **strong ordering** - if both ``x < y`` and ``y < x`` are false, objects are indistinguishable
- **weak ordering** - even if both ``x < y`` and ``y < x`` are false, objects may differ
- **partial ordering** - there is a possibility that for some ``x`` and ``y`` comparison has no answer

Examples:

- Integers have strong ordering. If for some integers ``x`` and ``y`` both ``x < y`` and ``y < x`` are false, they are indistinguishable.
- Case-insensitive strings have weak ordering. Even if for some ``x`` and ``y`` both ``x < y`` and ``y < x`` are false, the strings may differ.
- Square roots in real numbers domain: for some real numbers (e.g. ``-4``), there is no square root so for some pairs of numbers the order can not be determined.
- Partial ordering is present in floating-point numbers: some of them represent special values like ``NaN`` and ``infinity``. For practical reasons, comparisons of any floating-point values never invoke undefined behavior but special values break expected consistency - any comparison involving at least 1 special value always returns false (this even includes cases like 2 ``NaN``).
- Partial ordering is present in overload resolution:

  - :cch:`const T` is more cv-qualified than :cch:`T`.
  - :cch:`volatile T` is more cv-qualified than :cch:`T`.
  - :cch:`const volatile T` is more cv-qualified than :cch:`const T`.
  - :cch:`const volatile T` is more cv-qualified than :cch:`volatile T`.
  - There is no ordering specified between :cch:`const T` and :cch:`volatile T`. If a function has 2 such overloads and is given :cch:`T`, overload resolution will fail due to ambiguity.

..

    How about *partial equality*?

There is no such thing, at least in C++.

Strong and weak orderings should always satisfy:

- irreflexivity: ``x < x`` is always false
- asymmetry: if ``x < y`` is true then ``y < x`` is false
- transitivity: if ``x < y`` and ``y < z`` then ``x < z`` must be true
- exactly one of ``x < y``, ``x > y``, ``x == y`` must be true for any ``x`` and ``y``

Exercise
########

Which comparison categories are present in the following situations?

- points by the sum of their X, Y coordinates
- files by their size
- files by their paths
- users by their unique ID
- people by their birth date
- people by their ancestry tree

.. details::
    :summary: Answers

    - weak ordering (points 3,5 and 4,4 are equal)
    - weak ordering (files with same size can be different)
    - weak equality (symlinks can create multiple paths for the same file), weak ordering if we additionally consider sorting paths as strings
    - strong equality (IDs are unique so 2 identical IDs refer to the same user) or strong ordering (if IDs are treated as numbers and can be sorted)
    - weak ordering (date can be the same for different people)
    - partial ordering (for some pairs of people we can not determine their common ancestor)

Practice
########

:cch:`operator<=>` can return one of 3 ordering types, defined in :cch:`<compare>`. The types themselves are not enumerations but classes (and values implemented as :cch:`inline static constexpr$$$keyword keyword keyword` members) which allows to specify implicit convertions by writing non-:cch:`explicit` converting constructors.

:cch:`std::strong_ordering` is implicity-convertible to :cch:`std::weak_ordering` which is implicity-convertible to :cch:`std::partial_ordering`.

All values:

- :cch:`std::strong_ordering::less`
- :cch:`std::strong_ordering::equal`
- :cch:`std::strong_ordering::equivalent`
- :cch:`std::strong_ordering::greater`
- :cch:`std::weak_ordering::less`
- :cch:`std::weak_ordering::equivalent`
- :cch:`std::weak_ordering::greater`
- :cch:`std::partial_ordering::less`
- :cch:`std::partial_ordering::equivalent`
- :cch:`std::partial_ordering::greater`
- :cch:`std::partial_ordering::unordered`

**Equivalent** elements are treated the same way for the purpose of comparison but are distinguishable. **Equal** elements are truly identical (thus this value is only present in :cch:`std::strong_ordering`).

If every member of the class has defined :cch:`operator<=>` and the :cch:`operator<=>` definition is defaulted, you can use :cch:`auto` as a return type and the compiler will pick the most powerful ordering category that is possible. Built-in types are considered to have the operator defined.

You can call :cch:`operator<=>` and its result (one of standard library ordering types) can be compared with one of the terms listed above and also directly with literal :cch:`0`:

.. cch::
    :code_path: cmp_call.cpp
    :color_path: cmp_call.color

.. admonition:: note
  :class: note

  If the implementation of :cch:`operator<=>` is :cch:`= default` and :cch:`operator==` is not declared at all, then :cch:`operator==` is :cch:`= default` too. Otherwise :cch:`operator==` and :cch:`operator!=` are not defined.

..

    What's the reason behind special treatment of :cch:`operator==` and :cch:`operator!=`?

Optimization. Take strings as an example. Determining which of :cch:`"abc"` and :cch:`"abCD"$$$str` is greater requires a loop that goes through multiple characters (potentially expensive operation if strings are long and many first characters are equal). Determining whether they are equal is instant because equality can start by comparing length and only consider looping through characters if lengths are the same. In other words, for some types 2-way equivalence check can be much faster than 3-way comparison. Thus, if :cch:`operator<=>` is not :cch:`= default`, :cch:`operator==` should not be :cch:`= default` too.

Fraction class
##############

- Weak ordering is used because two equal fractions can have different representation (e.g. 1/2 vs 2/4).
- No operator is defaulted because the implementation is more complex than mere memberwise comparison.
- :cch:`operator==` is defined because the 2-way equivalence check can be more optimal than 3-way comparison.

.. cch::
    :code_path: fraction.cpp
    :color_path: fraction.color

Mixed-type comparisons
######################

Thanks to *rewritten candidates*, the example from previous lesson can be simplified to this code:

.. cch::
    :code_path: player_id.cpp
    :color_path: player_id.color

Lexicographical comparison
##########################

Just like in the previous lesson, you can use :cch:`std::tie` trick to avoid writing bug-prone code:

.. cch::
    :code_path: tuple_comparison.cpp
    :color_path: tuple_comparison.color

If there are no extra members and memberwise comparison is desired, the operator can be defined as :cch:`= default`.

Recommendations
###############

Using comparisons
=================

- Only call :cch:`operator<=>` if you truly need a 3-way comparison answer (for performance reasons). Examples:

  - If you only need to know whether 2 objects are equal, use :cch:`operator==`.
  - If you search only for a minimum element, comparing subsequent elements with the minimum one using :cch:`operator<` is enough.

- Don't implement :cch:`operator<=>` just because you need comparison for :cch:`std::map` or other container. If the type makes no sense in ordering (e.g. a complex number class) but you need something for a container it's much better to use a function object that only affects the container.

Implementing comparisons
========================

For any class type:

- If you want just equality, implement only :cch:`operator==`.

  - If you want it to compare all members in their order of appearance, you can :cch:`= default` it.

- If you want ordering, implement :cch:`operator<=>`.

  - If you want to compare all members in order of their appearance, you can :cch:`= default` it.
  - If you want to optimize equality checks, you can additionally implement :cch:`operator==`.
  - Don't define :cch:`operator<=>` with :cch:`std::partial_ordering` return type - it's very surprising when for some pair of objects all :cch:`x < y`, :cch:`x == y` and :cch:`x > y` can return :cch:`false`. Instead, write a free function named exactly ``partial_order`` and use this function (this specific name will also be searched by standard library templates).

Advanced features
#################

The standard library contains *niebloids* that can be used to compare objects and produce a result of specific comparison category (as long as the comparison is possible).

When writing generic code, it is recommended not to use :cch:`operator<=>` as not every type may have it defined. Instead, it is recommended to use a template like the one presented below that will check for :cch:`operator<=>` existence and fall back to other operators.

.. cch::
    :code_path: synth_three_way.cpp
    :color_path: synth_three_way.color

.. TODO any example usage? or move it to templates tutorial because it's too advanced?

Trivia
######

There was an idea to use the name :cch:`<=>$$$0pp_header` for the header :cch:`<compare>`\ [citation needed] but it was ultimately resigned from due to concern that ``=`` may not be in the set of supported characters for paths on some implementations.

----

This lesson has been based on:

- https://www.jonathanmueller.dev/talk/meetingcpp2019/
- https://youtube.com/watch?v=bysb-tzglqg
