.. title: 04 - arithmetic
.. slug: 04_arithmetic
.. description: arithmetic operators
.. author: Xeverous

Binary arithmetic operators
###########################

These should be very intuitive.

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

        double approx() const
        {
            return static_cast<double>(m_numerator) / m_denominator;
        }

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
        {
            // if denominator is negative, result must be reversed
            if (lhs.denominator() > 0) // e.g. 2/4 < 3/4
                return lhs.numerator() < rhs.numerator();
            else // e.g. 3/-4 < 2/-4
                return rhs.numerator() < lhs.numerator();
        }

        // if denominator signs differ, result must be reversed
        if ((lhs.denominator() > 0) == (rhs.denominator() > 0))
            return lhs.numerator() * rhs.denominator() < rhs.numerator() * lhs.denominator();
        else
            return rhs.numerator() * lhs.denominator() < lhs.numerator() * rhs.denominator();
    }

    bool operator> (fraction lhs, fraction rhs) { return rhs < lhs; }
    bool operator<=(fraction lhs, fraction rhs) { return !(lhs > rhs); }
    bool operator>=(fraction lhs, fraction rhs) { return !(lhs < rhs); }

    fraction operator+(fraction lhs, fraction rhs)
    {
        // a/b + c/d = (ad + cb)/bd

        const int new_numerator =
            lhs.numerator() * rhs.denominator() +
            rhs.numerator() * lhs.denominator();
        const int new_denominator = lhs.denominator() * rhs.denominator();

        fraction result(new_numerator, new_denominator);
        result.simplify();
        return result;
    }

    fraction operator-(fraction lhs, fraction rhs)
    {
        // a/b - c/d = (ad - cb)/bd

        const int new_numerator =
            lhs.numerator() * rhs.denominator() -
            rhs.numerator() * lhs.denominator();
        const int new_denominator = lhs.denominator() * rhs.denominator();

        fraction result(new_numerator, new_denominator);
        result.simplify();
        return result;
    }

    fraction operator*(fraction lhs, fraction rhs)
    {
        // a/b * c/d = ac/bd

        fraction result(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
        result.simplify();
        return result;
    }

    fraction operator/(fraction lhs, fraction rhs)
    {
        assert(rhs != 0); // can't divide by 0

        // a/b / c/d = a/b * d/c = ad/bc

        fraction result(lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
        result.simplify();
        return result;
    }

    fraction operator%(fraction lhs, fraction rhs)
    {
        assert(rhs != 0); // can't modulo by 0

        // a/b % c/d = (ad % bc)/bd

        fraction result(
            (lhs.numerator() * rhs.denominator()) % (rhs.numerator() * lhs.denominator()),
            lhs.denominator() * rhs.denominator());
        result.simplify();
        return result;
    }

    int main()
    {
        assert(fraction(1, 2) + fraction(1, 4) == fraction(3, 4));
        assert(fraction(1, 2) - fraction(1, 4) == fraction(1, 4));

        assert(fraction(3, 5) * fraction(4, 3) == fraction(4, 5));
        assert(fraction(3, 5) / fraction(3, 4) == fraction(4, 5));

        assert(fraction(3, 5) * fraction(4, -3) == fraction(-4, 5));
        assert(fraction(3, 5) / fraction(3, -4) == fraction(-4, 5));

        assert(fraction(2, 1) % fraction(3, 10) == fraction(1, 5));
        assert(fraction(2, 1) % fraction(3, -10) == fraction(1, 5));
        assert(fraction(2, 1) % fraction(-3, 10) == fraction(1, 5));
        assert(fraction(-2, 1) % fraction(3, 10) == fraction(-1, 5));
        assert(fraction(2, -1) % fraction(3, 10) == fraction(-1, 5));

        assert((1 - fraction(1, 2)).approx() == 0.5);
    }

Unary arithmetic operators
##########################

You might already used unary minus in expressions like :cch:`x = -x`. Unary plus isn't very useful (it does not modify value for built-in integer and floating-point types) but exists for consistency. Unary plus is used in more arcane applications of operator overloading such as EDSLs.

Unary plus and minus can be overloaded both as free functions and as member functions.

.. TODO any recommendation which to choose? Some types in standard library implement them as non-member (`std::complex`) and some as member (`std::chrono::duration`).

.. TODO *this explained when???

.. TOCOLOR

.. code::

    // as member functions (code should be inside class definition)
    fraction operator+() const
    {
        return *this;
    }

    fraction operator-() const
    {
        return {-numerator(), denominator()};
    }

    // as free functions
    fraction operator+(fraction fr)
    {
        return fr;
    }

    fraction operator-(fraction fr)
    {
        return {-fr.numerator(), fr.denominator()};
    }

.. TOCOLOR

.. code::

    assert(fraction(1, 2) == +fraction(1, 2));
    assert(fraction(1, 2) == -fraction(-1, 2));
    assert(fraction(1, 2) == -fraction(1, -2));
