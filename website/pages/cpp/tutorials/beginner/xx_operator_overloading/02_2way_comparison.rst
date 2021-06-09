.. title: 02 - 2-way comparison
.. slug: 02_2way_comparison
.. description: 2-way comparison operators
.. author: Xeverous

We start at the simplest operators - ones which do not need to modify the object

Equality
########

.. TOCOLOR

.. code::

    #include <iostream>
    #include <cassert>

    // (greatest common divisor)
    // if you have C++17, you can remove this function and use std::gcd from <numeric>
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    class fraction
    {
    private:
        int m_numerator = 0;
        int m_denominator = 1;

        static int make_valid_denominator(int value)
        {
            if (value == 0)
                return 1;
            else
                return value;
        }

    public:
        fraction(int numerator = 0, int denominator = 1)
        : m_numerator(numerator)
        , m_denominator(make_valid_denominator(denominator))
        {}

        void simplify()
        {
            const int n = gcd(m_numerator, m_denominator);
            m_numerator /= n;
            m_denominator /= n;
        }

        int numerator() const { return m_numerator; }
        int denominator() const { return m_denominator; }

        void print() const
        {
            std::cout << m_numerator << "/" << m_denominator;
        }
    };

    bool operator==(fraction lhs, fraction rhs)
    {
        if (lhs.denominator() == rhs.denominator())
            return lhs.numerator() == rhs.numerator();

        // a/b == c/d is same as ad/bd == bc/bd
        // we don't need to compute new denominators, just compare ad and bc
        return lhs.numerator() * rhs.denominator() == rhs.numerator() * lhs.denominator();
    }

    bool operator!=(fraction lhs, fraction rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(fraction lhs, fraction rhs)
    {
        if (lhs.denominator() == rhs.denominator())
            return lhs.numerator() < rhs.numerator();

        return lhs.numerator() * rhs.denominator() < rhs.numerator() * lhs.denominator();
    }

    bool operator> (fraction lhs, fraction rhs) { return rhs < lhs; }
    bool operator<=(fraction lhs, fraction rhs) { return !(lhs > rhs); }
    bool operator>=(fraction lhs, fraction rhs) { return !(lhs < rhs); }

    int main()
    {
        assert(fraction(1, 2) == fraction(2, 4));
        assert(fraction(1, 2) != fraction(-1, 2));
        assert(fraction(1, 2) != fraction(1, -2));
        assert(fraction(1, 2) == fraction(-1, -2));

        assert(fraction(2, 6) == fraction(3, 9));
    }

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

.. TOCOLOR

.. code::

    #include <iostream>
    #include <cassert>

    // (greatest common divisor)
    // if you have C++17, you can remove this function and use std::gcd from <numeric>
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    class fraction
    {
    private:
        int m_numerator = 0;
        int m_denominator = 1;

        static int make_valid_denominator(int value)
        {
            if (value == 0)
                return 1;
            else
                return value;
        }

    public:
        fraction(int numerator = 0, int denominator = 1)
        : m_numerator(numerator)
        , m_denominator(make_valid_denominator(denominator))
        {}

        void simplify()
        {
            const int n = gcd(m_numerator, m_denominator);
            m_numerator /= n;
            m_denominator /= n;
        }

        int numerator() const { return m_numerator; }
        int denominator() const { return m_denominator; }

        void print() const
        {
            std::cout << m_numerator << "/" << m_denominator;
        }

        // BAD: don't overload such operators as members

        bool operator==(fraction rhs) const
        {
            if (denominator() == rhs.denominator())
                return numerator() == rhs.numerator();

            return numerator() * rhs.denominator() == rhs.numerator() * denominator();
        }

        bool operator!=(fraction rhs) const
        {
            return !(*this == rhs);
        }

        bool operator<(fraction rhs) const
        {
            if (denominator() == rhs.denominator())
                return numerator() < rhs.numerator();

            return numerator() * rhs.denominator() < rhs.numerator() * denominator();
        }

        bool operator> (fraction rhs) const { return rhs < *this; }
        bool operator<=(fraction rhs) const { return !(*this > rhs); }
        bool operator>=(fraction rhs) const { return !(*this < rhs); }
    };

    int main()
    {
        fraction fr(2, 1);

        // fine: second operand undergoes implicit convertion (2 is treated as fraction(2))
        assert(fr == 2);
        assert(fr.operator==(2));

        // bad: first operand can not undergo implicit convertion
        assert(2 == fr);
        assert(2.operator==(fr));
    }

The cause of this assymetry is the fact that if you call a member function, it's already known on what object the function is called. The reverse situation - searching for member functions on a different type is not possible.

Thus, "symmetrical" (commutative binary) operators should be implemented as free functions.

3-way helpers
#############

Sometimes you might already have a comparison helper in the form of a 2-argument function, which returns negative, zero or positive number depending on the ordering between elements. In such case, all comparison operators can use the helper:

.. TOCOLOR

.. code::

    class report;
    int compare(const report& lhs, const report& rhs);

    bool operator==(const report& lhs, const report& rhs) { return compare(lhs, rhs) == 0; }
    bool operator!=(const report& lhs, const report& rhs) { return compare(lhs, rhs) != 0; }
    bool operator< (const report& lhs, const report& rhs) { return compare(lhs, rhs) <  0; }
    bool operator> (const report& lhs, const report& rhs) { return compare(lhs, rhs) >  0; }
    bool operator<=(const report& lhs, const report& rhs) { return compare(lhs, rhs) <= 0; }
    bool operator>=(const report& lhs, const report& rhs) { return compare(lhs, rhs) >= 0; }

Lexicographical comparison
##########################

If you have a type with multiple members and need to implement lexicographical comparison, you can use :cch:`std::tie` (which creates :cch:`std::tuple` of lvalue references) and rely on tuple's comparison operators:

.. TOCOLOR

.. code::

    #include <tuple>

    struct package
    {
        int rack;
        int shelf;
        int position;
    };

    // bug-prone implementation
    bool operator<(package lhs, package rhs)
    {
        if (lhs.rack != rhs.rack)
            return lhs.rack < rhs.rack;

        if (lhs.shelf != rhs.shelf)
            return lhs.shelf < rhs.shelf;

        return lhs.position < rhs.position;
    }

    // same behavior, but much cleaner
    bool operator<(package lhs, package rhs)
    {
        // orders elements by rack first, then by shelf, then by position
        return std::tie(lhs.rack, lhs.shelf, lhs.position)
             < std::tie(rhs.rack, rhs.shelf, rhs.position);
    }
