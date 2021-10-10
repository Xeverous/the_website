#include <iostream>

void func(int& x)
{
	x *= 2;
	std::cout << "x inside function: " << x << "\n";
}

int main()
{
	func(10);

	int& ref = 10;
	func(ref);
}
