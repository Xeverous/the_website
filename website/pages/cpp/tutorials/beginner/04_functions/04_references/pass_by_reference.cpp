#include <iostream>

void func(int& x)
{
	x *= 2;
	std::cout << "x inside function: " << x << "\n";
}

int main()
{
	int x = 10;
	std::cout << "x before function call: " << x << "\n";
	func(x);
	std::cout << "x after function call: " << x << "\n";
}
