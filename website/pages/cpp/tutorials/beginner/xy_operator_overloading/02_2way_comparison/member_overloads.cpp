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

	// BAD: don't overload comparison operators as members

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
};

int main()
{
	fraction fr(2, 1);

	// fine: second operand undergoes implicit convertion (2 is treated as fraction(2))
	assert(fr == 2);
	assert(fr.operator==(2));

	// bad: first operand can not undergo implicit convertion
	assert(2 == fr);          // compiler error: no match for operator==(int, fraction)
	assert(2.operator==(fr)); // syntax error
}
