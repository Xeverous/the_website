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

class fraction
{
public:
	int numerator;
	int denominator;

	void simplify()
	{
		const int n = gcd(numerator, denominator);
		numerator /= n;
		denominator /= n;
	}

	void print()
	{
		std::cout << numerator << "/" << denominator << "\n";
	}
};

int main()
{
	fraction fr1{2, 6};
	fraction fr2{5, 10};

	fr1.print();
	fr2.print();
	fr1.simplify();
	fr2.simplify();
	fr1.print();
	fr2.print();
}
