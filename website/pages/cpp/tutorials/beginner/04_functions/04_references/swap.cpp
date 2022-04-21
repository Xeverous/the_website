#include <utility>
#include <iostream>

int main()
{
	int x = 1;
	int y = 2;
	std::swap(x, y); // both parameters taken by non-const lvalue reference
	std::cout << "x = " << x << "\ny = " << y << "\n";
}
