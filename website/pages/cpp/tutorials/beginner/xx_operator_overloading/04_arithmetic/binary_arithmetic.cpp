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
}
