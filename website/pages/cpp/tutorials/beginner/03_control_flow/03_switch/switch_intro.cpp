#include <iostream>

int main()
{
	std::cout << "Enter a number: ";
	int x = 0;
	std::cin >> x;

	switch (x)
	{
		case 3:
			std::cout << "you entered 3 or a higher number\n";
		case 2:
			std::cout << "you entered 2 or a higher number\n";
		case 1:
			std::cout << "you entered 1 or a higher number\n";
		case 0:
			std::cout << "you entered 0 or a higher number\n";
	}
}
