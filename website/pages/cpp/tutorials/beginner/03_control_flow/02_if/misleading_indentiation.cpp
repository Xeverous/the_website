#include <iostream>

int main()
{
	int x = 6;

	if (x % 2 == 0)
		std::cout << x << " is even\n";

		if (x % 4 == 0)
			std::cout << x << " is divisible by 4\n";
	else
		std::cout << x << " is odd\n";
}
