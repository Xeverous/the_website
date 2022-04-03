#include <iostream>

int make_valid_denominator(int value)
{
	if (value == 0)
		return 1;
	else
		return value;
}

class fraction
{
private:
	int numerator = 0;
	int denominator = 1;

public:
	// constructor
	fraction(int numerator, int denominator)
	{
		set(numerator, denominator);
	}

	void set(int count, int denom)
	{
		numerator = count;
		denominator = make_valid_denominator(denom);
	}
};

int main()
{
	// this is how you use a constructor to create an object
	fraction fr1(1, 2);

	// some people prefer to do this because it looks like a function call
	// the ctor creates a temporary object, then another object is assigned from it
	// since C++17 this is guuaranteed to be optimized to avoid temporary and assignment
	auto fr2 = fraction(2, 3);
}
