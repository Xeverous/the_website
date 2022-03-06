.. title: 05 - compound assignment
.. slug: 05_compound_assignment
.. description: compound assignment operators
.. author: Xeverous

Compound assignment operators can be defined both as free functions and as member functions. Member functions are preferred for 2 reasons:

- The operation has no symmetry (:cch:`a += b$$$var_local += var_local` is not the same as :cch:`b += a$$$var_local += var_local`).
- A free function must return by value (recall problems with references to temporaries). Member functions can return a reference to :cch:`*this`, which is useful for chained operations like :cch:`a = b = c = d$$$var_local = var_local = var_local = var_local`.

To avoid code duplication, there are 2 choices:

- compound assignments reuse other operators
- other operators reuse compound assignments

The second one is preferred.

.. TODO why second one is preferred?

Updated fraction class:

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

        fraction& operator+=(fraction other)
        {
            m_numerator = numerator() * other.denominator() + other.numerator() * denominator();
            m_denominator = denominator() * other.denominator();

            simplify();
            return *this;
        }

        fraction& operator-=(fraction other)
        {
            m_numerator = numerator() * other.denominator() - other.numerator() * denominator();
            m_denominator = denominator() * other.denominator();

            simplify();
            return *this;
        }

        fraction& operator*=(fraction other)
        {
            m_numerator *= other.numerator();
            m_denominator *= other.denominator();

            simplify();
            return *this;
        }

        fraction& operator/=(fraction other)
        {
            // note: we could write assert(other != 0) but
            // at this point in code operator!= has not been defined yet
            // a different solution would be to declare operator/= and implement it later
            assert(other.numerator() != 0);
            m_numerator *= other.denominator();
            m_denominator *= other.numerator();

            simplify();
            return *this;
        }

        fraction& operator%=(fraction other)
        {
            assert(other.numerator() != 0);
            m_numerator = (numerator() * other.denominator()) % (other.numerator() * denominator());
            m_denominator *= other.denominator();

            simplify();
            return *this;
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

    fraction operator+(fraction lhs, fraction rhs) { return lhs += rhs; }
    fraction operator-(fraction lhs, fraction rhs) { return lhs -= rhs; }
    fraction operator*(fraction lhs, fraction rhs) { return lhs *= rhs; }
    fraction operator/(fraction lhs, fraction rhs) { return lhs /= rhs; }
    fraction operator%(fraction lhs, fraction rhs) { return lhs %= rhs; }

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
    }
