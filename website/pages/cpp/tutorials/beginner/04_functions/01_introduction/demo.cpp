#include <iostream>

int add(int x, int y)
{
	return x + y;
}

int multiply(int x, int y)
{
	return x * y;
}

int passthrough(int x)
{
	return x;
}

int main()
{
	// obviously such code is not written in production
	// it's here to demonstrate nested function calls
	std::cout << add(1, multiply(add(-4, 7), 2)) << "\n";
	std::cout << passthrough(passthrough(passthrough(passthrough(1)))) << "\n";
}
