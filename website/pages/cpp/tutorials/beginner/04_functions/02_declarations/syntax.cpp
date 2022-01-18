#include <iostream>

// note 1: declarations end with ;
// note 2: declarations do not have to specify parameter names, only types
void greet();
int test(int, int);

int main()
{
	// ok, functions were declared
	greet();
	std::cout << test(2, 3) << "\n";
}

int test(int x, int y)
{
	return x * y;
}

void greet()
{
	std::cout << "hello, world\n";
}
