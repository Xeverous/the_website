#include <iostream>

int main()
{
	int x = 10;
	int& ref1 = x;
	int& ref2 = ref1;
	int& ref3 = ref2;

	++ref3;

	std::cout << x; // 11

	// syntax error: there is no such thing as nested references
	// int& & ref4 = ref3;

	// this is something different and will be covered later
	// int&& ref5 = ref3;
}
