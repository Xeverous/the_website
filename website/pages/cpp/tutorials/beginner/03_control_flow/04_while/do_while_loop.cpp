#include <iostream>

int main()
{
	int x = 0;
	do
	{
		std::cout << "Enter a non-negative number: ";
		std::cin >> x;
	} while (x < 0);
	//             ^ spot the semicolon
}
