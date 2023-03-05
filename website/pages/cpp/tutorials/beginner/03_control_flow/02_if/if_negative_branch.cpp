#include <iostream>

int main()
{
	std::cout << "Enter a number: ";
	int x = 0;
	std::cin >> x;

	if (x % 2 == 0)
	{
		// positive branch - executed only if condition is true
		std::cout << x << " is even (divisible by 2)\n";
	}
	else
	{
		// negative branch - executed only if condition is false
		std::cout << x << " is odd\n";
	}
}
