#include <iostream>

int main()
{
	int x = 0;
	while (true)
	{
		std::cout << "Enter a non-negative number: ";
		std::cin >> x;

		if (x >= 0)
			break;
	}
}
