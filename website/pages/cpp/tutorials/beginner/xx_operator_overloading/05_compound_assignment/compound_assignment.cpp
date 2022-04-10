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
	int m_numerator;
	int m_denominator;

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

	fraction& operator+=(fraction rhs)
	{
		m_numerator = numerator() * rhs.denominator() + rhs.numerator() * denominator();
		m_denominator = denominator() * rhs.denominator();

		simplify();
		return *this;
	}

	fraction& operator-=(fraction rhs)
	{
		m_numerator = numerator() * rhs.denominator() - rhs.numerator() * denominator();
		m_denominator = denominator() * rhs.denominator();

		simplify();
		return *this;
	}

	fraction& operator*=(fraction rhs)
	{
		m_numerator *= rhs.numerator();
		m_denominator *= rhs.denominator();

		simplify();
		return *this;
	}

	fraction& operator/=(fraction rhs)
	{
		// note: we could write assert(rhs != 0) but
		// at this point in code operator!= has not been defined yet
		// a different solution would be to declare operator/= and implement it later
		assert(rhs.numerator() != 0);
		m_numerator *= rhs.denominator();
		m_denominator *= rhs.numerator();

		simplify();
		return *this;
	}

	fraction& operator%=(fraction rhs)
	{
		assert(rhs.numerator() != 0);
		m_numerator = (numerator() * rhs.denominator()) % (rhs.numerator() * denominator());
		m_denominator *= rhs.denominator();

		simplify();
		return *this;
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

// Just look how short these are!
// The expression modifies lhs which is then returned by reference (from
// compound version) which is then returned by value from the non-compound version.
// If the type is expensive, second parameter should be taken by const reference
// (first by value because it has to be copied, modified and returned).
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
