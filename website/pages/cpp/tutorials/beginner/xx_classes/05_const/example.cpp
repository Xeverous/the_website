#include <iostream>

// (greatest common divisor)
// if you have C++17, you can remove this function and use std::gcd from <numeric>
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

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
	fraction(int numerator = 0, int denominator = 1)
	: numerator(numerator)
	, denominator(make_valid_denominator(denominator))
	{}

	void simplify()
	{
		const int n = gcd(numerator, denominator);
		numerator /= n;
		denominator /= n;
	}

	// note where the const keyword is placed
	// "const double approx()" would affect return type, not the function
	double approx() const
	{
		return static_cast<double>(numerator) / denominator;
	}

	void print() const
	{
		std::cout << numerator << "/" << denominator;
	}
};

/*
 * Because fraction class is small and inexpensive to copy,
 * it should be passed by value instead of const reference.
 * Const reference is used here to demonstrate potential
 * errors of calling non-const methods on const objects.
 */
void print_details(const fraction& fr)
{
	fr.print();
	std::cout << ", approx. " << fr.approx() << "\n";

	// fr.simplify(); // error: can not call non-const member function on const-qualified object
}

void test(fraction fr)
{
	print_details(fr);
	fr.simplify();
	std::cout << "after simplification:\n";
	print_details(fr);
	std::cout << "\n";
}

int main()
{
	test(fraction(8, 12));
	test(fraction(8, -12));
	test(fraction(-8, -12));
}
