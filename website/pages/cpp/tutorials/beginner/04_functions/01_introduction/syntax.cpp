#include <iostream>
#include <cmath>

// return type: double
// name: square
// parameters (1): double
double square(double x)
{
	return x * x;
}

// return type: long double
// name: herons_formula
// parameters (3): all of type long double
long double herons_formula(long double a, long double b, long double c)
{
	const long double s = (a + b + c) / 2.0;
	// <cmath> provides common mathematical functions, including square root
	return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

// return type: int
// name: main
// parameters (0)
int main()
{
	std::cout << square(2.5) << "\n";
	std::cout << square(-2.5) << "\n";
	std::cout << herons_formula(4, 13, 15) << "\n";
}
