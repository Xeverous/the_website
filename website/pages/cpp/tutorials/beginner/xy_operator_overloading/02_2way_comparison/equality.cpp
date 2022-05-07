#include <iostream>
#include <cassert>

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

int main()
{
	assert(fraction(1, 2) == fraction(2, 4));
	assert(fraction(1, 2) != fraction(-1, 2));
	assert(fraction(1, 2) != fraction(1, -2));
	assert(fraction(1, 2) == fraction(-1, -2));

	assert(fraction(2, 6) == fraction(3, 9));

	assert(fraction(3, 5) < fraction(2, 3));
	assert(fraction(3, 5) > fraction(-2, 3));
	assert(fraction(3, 5) > fraction(2, -3));
	assert(fraction(3, 5) < fraction(-2, -3));
}
