#include <iostream>

int main()
{
	std::cout << "Enter a number: ";
	int x = 0;
	std::cin >> x;

	// for 1, prints "12345"
	// for 2, prints "2345"
	// for 3, prints "345"
	// for 4 and 5, prints "45"
	// for 6, prints "6"
	// for anything else, does nothing
	switch (x)
	{
		case 1:
			std::cout << "1";
		case 2:
			std::cout << "2";
		case 3:
			std::cout << "3";
		case 4:
		case 5:
			std::cout << "45";
			break;
		case 6:
			std::cout << "6";
	}
}
