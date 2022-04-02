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
private:
	int numerator = 0;
	int denominator = 1;

public:
	void set(int count, int denom)
	{
		numerator = count;

		if (denom == 0)
			denominator = 1;
		else
			denominator = denom;
	}

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
	// no longer possible
	// having private members disables this kind of initialization
	// this will be fixed later with constructors
	// fraction fr1{2, 6};
	// fraction fr2{5, 10};

	fraction fr1; // will inialize members as specified in class definition
	fr1.set(2, 6);
	fraction fr2;
	fr2.set(5, 10);

	// fr1.denominator = 0; // error: can not access private member

	fr1.print();
	fr2.print();
	fr1.simplify();
	fr2.simplify();
	fr1.print();
	fr2.print();
}
