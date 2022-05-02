#include <iostream>

int main()
{
	std::cout << "Enter 2 numbers\n";
	int x;
	int y;
	std::cin >> x >> y; // x is read first, then y
	std::cout << "x = " << x << "\ny = " << y << "\n";
}
