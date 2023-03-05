#include <iostream>

int main()
{
	std::cout << "Enter a number: ";
	int x = 0;
	std::cin >> x;

	if (x == 0)
	{
		std::cout << "You entered zero.\n";
	}
	else
	{
		while (x % 2 == 0)
		{
			std::cout << "dividing " << x << "\n";
			x /= 2; // equivalent to x = x / 2
		}

		std::cout << "The final, odd value is " << x << ".\n";
	}
}
