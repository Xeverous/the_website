.. title: 03 - 3-way comparison
.. slug: 03_3way_comparison
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

C++20 has made overload resolution smarter for comparison operators with the feature of *rewritten candidates* - if :cch:`x != y` is not valid, compiler will try :cch:`!(x == y)` and analogically for other operators. Rewritten candidates are considered for both member and non-member overloads.

Thus:

- The guideline to implement "symmetrical" operators as non-members no longer applies for equality and comparison operators.
- You no longer need to implement so many operator overloads. The boilerplate work is now done by the compiler.
- Some compiler errors have been improved.

Defaulted implementation
########################

Another improvement is that you can now :cch:`= default` operators if they are member functions. They will compare class members in order of their appearance.

The spaceship operator
######################

:cch:`operator<=>` represents 3-way comparison. It provides more information so a :cch:`bool` return type is not enough for it.

Before delving into what should be used instead of :cch:`bool`, you should first understand logical concepts that motivated multiple choices for the return type.

    Can I call ``<=>`` a TIE Fighter?

No:

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

:cch:`operator<=>` can return one of 3 ordering types, defined in :cch:`<compare>`.

All possible values:

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

If every member of the class has defined :cch:`operator<=>` and the :cch:`operator<=>` definition is defaulted, you can use :cch:`auto` as a return type and the compiler will pick most powerful ordering category that is possible.

You can call :cch:`operator<=>` and its result (one of standard library ordering types) can be compared with one of the terms listed above and also directly with literal ``0``:

.. TOCOLOR

.. code::

    const auto cmp = x <=> y; // cmp will be std::*_ordering
    if (cmp < 0)
        std::cout << "x < y";
    else if (cmp > 0)
        std::cout << "x > y";
    else
        std::cout << "x == y";

For the implementation of :cch:`operator<=>`:

- If it's defaulted and :cch:`operator==` is not declared at all, then :cch:`operator==` is implicitly defaulted.
- If it's custom then :cch:`operator==` and :cch:`operator!=` are not defined.

..

    What's the point of special treatment of :cch:`operator==` in these cases?

Optimization. Take strings as an example. Determining which of :cch:`"abc"` and :cch:`"abCD"$$$str` is greater requires a loop that goes through multiple characters. Determining whether they are equal is instant because equality can start by comparing length and only consider looping through characters if lengths are the same.

Fraction class
##############

- Weak ordering is used since two equal fractions may have different values (e.g. 1/2 vs 2/4).
- :cch:`operator==` is defined because checking for equality has slighly less operations to perform.

.. TOCOLOR

.. code::

    // (all inside class body)

    bool operator==(fraction rhs) const
    {
        if (denominator() == rhs.denominator())
            return numerator() == rhs.numerator();

        return numerator() * rhs.denominator() == rhs.numerator() * denominator();
    }

    std::weak_ordering operator<=>(fraction rhs) const
    {
        if (denominator() == rhs.denominator())
        {
            if (denominator() > 0)
            {
                if (numerator() < rhs.numerator())
                    return std::weak_ordering::less;
                else if (numerator() > rhs.numerator())
                    return std::weak_ordering::greater;
                else
                    return std::weak_ordering::equivalent;
            }
            else
            {
                if (numerator() < rhs.numerator())
                    return std::weak_ordering::greater;
                else if (numerator() > rhs.numerator())
                    return std::weak_ordering::less;
                else
                    return std::weak_ordering::equivalent;
            }
        }

        const int new_lhs_numerator = lhs.numerator() * rhs.denominator();
        const int new_rhs_numerator = rhs.numerator() * lhs.denominator();

        if ((lhs.denominator() > 0) == (rhs.denominator() > 0))
        {
            if (new_lhs_numerator < new_rhs_numerator)
                return std::weak_ordering::less;
            else if (new_lhs_numerator > new_rhs_numerator)
                return std::weak_ordering::greater;
            else
                return std::weak_ordering::equivalent;
        }
        else
        {
            if (new_lhs_numerator < new_rhs_numerator)
                return std::weak_ordering::greater;
            else if (new_lhs_numerator > new_rhs_numerator)
                return std::weak_ordering::less;
            else
                return std::weak_ordering::equivalent;
        }
    }

Mixed-type comparisons
######################

.. this section requres explanation of autogenerated comparisons

Recall player example from previous lesson - now it can be simplified to this code:

.. TOCOLOR

.. code::

    class player
    {
    private:
        int id;
        // lots of other fields... (potentially expensive to construct)

    public:
        // [...]

        bool operator==(const player& rhs) const
        {
            return id == rhs.id;
        }

        bool operator==(int other_id) const
        {
            return id == other_id;
        }
    };

Lexicographical comparison
##########################

Just like in previous lesson, you can use :cch:`std::tie` trick to avoid writing bug-prone code:

.. TOCOLOR

.. code::

    #include <tuple>

    struct package
    {
        int rack;
        int shelf;
        int position;
        // [...] some other members that you don't want to use in comparison

        auto operator<=>(package rhs) const
        {
            return std::tie(lhs.rack, lhs.shelf, lhs.position)
               <=> std::tie(rhs.rack, rhs.shelf, rhs.position);
        }
    };

If there were no extra members, the operator could be defined using :cch:`= default`.

Recommendations
###############

Using comparisons
=================

- Only call :cch:`operator<=>` if you truly need a 3-way comparison answer (for performance reasons). Examples:

  - If you only need to know whether 2 objects are equal, use :cch:`operator==`.
  - If you search only for a minimum element, comparing subsequent elements with the minimum one using :cch:`operator<` is enough.

- Don't implement :cch:`operator<=>` just because you need something for :cch:`std::map` or other parts of the standard library. If the type makes no sense in ordering (e.g. a complex number class) but you need something for a container it's much better to use a function object that only affects the container.

Implementing comparisons
========================

For any class type:

- If you want just equality, implement only :cch:`operator==`.

  - If you want it to compare all members in their order of appearance, you can :cch:`= default` it.

- If you want ordering, implement :cch:`operator<=>`.

  - If you want it to compare all members in their order of appearance, you can :cch:`= default` it.
  - If you want to optimize equality checks, you can additionally implement :cch:`operator==`.
  - Don't define :cch:`operator<=>` with :cch:`std::partial_ordering` return type - it's very surprising when for some pair of objects all :cch:`x < y`, :cch:`x == y` and :cch:`x > y` can return :cch:`false`. Instead, write a free function named exactly ``partial_order`` and use this function.

Advanced features
#################

The standard library contains *niebloids* that can be used to compare objects and produce a result of specific comparison category (as long as the comparison is possible): :cch:`std::strong_order`, :cch:`std::weak_order` and :cch:`std::partial_order`.

When writing generic code, it is recommended not to use :cch:`operator<=>` as not every type may have it defined. Instead, it is recommended to use a template like the one presented below that will check for :cch:`operator<=>` existence and fall back to other operators.

.. TOCOLOR

.. code::

    #include <compare>
    #include <type_traits>

    struct synth_three_way_t
    {
        template <typename T, std::totally_ordered_with<T> U>
        constexpr auto operator()(const T& lhs, const U& rhs) const
        {
            if constexpr (std::three_way_comparable_with<T, U>)
            {
                return lhs <=> rhs;
            }
            else
            {
                if (lhs == rhs)
                    return std::weak_ordering::equal;
                else if (lhs < rhs)
                    return std::weak_ordering::less;
                else
                    return std::weak_ordering::greater;
            }
        }
    };
    inline constexpr synth_three_way_t synth_three_way;

    template <typename T, typename U = T>
    using synth_three_way_category
        = decltype(synth_three_way(std::declval<const T&>(), std::declval<const U&>()));

Trivia
######

There was an idea to use the name :cch:`<=>$$$0pp_header` for the header :cch:`<compare>`\ [citation needed] but it was ultimately resigned from due to concern that ``=`` may not be in the set of supported characters for paths on some implementations.

----

This lesson has been based on:

- https://www.jonathanmueller.dev/talk/meetingcpp2019/
- https://youtube.com/watch?v=bysb-tzglqg
