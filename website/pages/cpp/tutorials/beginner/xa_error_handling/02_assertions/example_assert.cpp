#include <iostream>
#include <cassert>

int divide(int x, int y)
{
	assert(y != 0); // integer division by 0 is UB
	return x / y;
}

int main()
{
	int x = 0;
	int y = 0;
	std::cout << "enter x: ";
	std::cin >> x;
	std::cout << "enter y: ";
	std::cin >> y;
	std::cout << "result: " << divide(x, y);
}
