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

	int numerator() const
	{
		return m_numerator;
	}

	void numerator(int value)
	{
		m_numerator = value;
	}

	int denominator() const
	{
		return m_denominator;
	}

	void denominator(int value)
	{
		m_denominator = make_valid_denominator(value);
	}

	void print(std::ostream& os = std::cout) const
	{
		os << m_numerator << "/" << m_denominator;
	}

	double approx() const
	{
		return static_cast<double>(m_numerator) / m_denominator;
	}

	operator double() const
	{
		return approx();
	}

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

	fraction& operator++() // (prefix)
	{
		m_numerator += m_denominator;
		return *this;
	}

	fraction& operator--() // (prefix)
	{
		m_numerator -= m_denominator;
		return *this;
	}

	fraction operator++(int) // (postfix)
	{
		fraction old = *this;
		operator++();
		return old;
	}

	fraction operator--(int) // (postfix)
	{
		fraction old = *this;
		operator--();
		return old;
	}

private:
	static int make_valid_denominator(int value)
	{
		if (value == 0)
			return 1;
		else
			return value;
	}

	int m_numerator;
	int m_denominator;
};

bool operator==(fraction lhs, fraction rhs)
{
	if (lhs.denominator() == rhs.denominator())
		return lhs.numerator() == rhs.numerator();

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

fraction operator+(fraction lhs, fraction rhs) { return lhs += rhs; }
fraction operator-(fraction lhs, fraction rhs) { return lhs -= rhs; }
fraction operator*(fraction lhs, fraction rhs) { return lhs *= rhs; }
fraction operator/(fraction lhs, fraction rhs) { return lhs /= rhs; }
fraction operator%(fraction lhs, fraction rhs) { return lhs %= rhs; }

std::ostream& operator<<(std::ostream& os, fraction fr)
{
	fr.print(os);
	return os;
}
