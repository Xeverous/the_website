#include <iostream>

int add(int x, int y)
{
	return x + y;
}

int multiply(int x, int y)
{
	return x * y;
}

int passthrough(int x)
{
	return x;
}

int main()
{
	// some stupid examples to demonstrate nested calls
	// output of one function call is the input to another call
	std::cout << add(1, multiply(add(-4, 7), 2)) << "\n";
	std::cout << passthrough(passthrough(passthrough(passthrough(1)))) << "\n";

	// names do not matter, only types
	// here variables are called a and b, and by their position within ()
	// they match function parameters x and y
	int a = 2;
	int b = 3;
	add(a, b); // result discarded (will not be printed)
}
