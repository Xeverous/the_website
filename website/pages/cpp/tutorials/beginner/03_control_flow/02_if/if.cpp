#include <iostream>

int main()
{
	std::cout << "Enter a number: ";
	int x = 0;
	std::cin >> x;

	if (x % 2 == 0)
	{
		std::cout << x << " is even (divisible by 2)\n";
	}
}
