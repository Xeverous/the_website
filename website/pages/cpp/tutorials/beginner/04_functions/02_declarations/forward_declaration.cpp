#include <iostream>

void bar(int x);

void foo(int x)
{
	if (x == 0)
		return;

	std::cout << "foo: " << x << "\n";
	bar(x - 1); // OK: bar declared
}

void bar(int x)
{
	if (x == 0)
		return;

	std::cout << "bar: " << x << "\n";
	foo(x - 1); // OK: foo declared (through foo definition)
}

int main()
{
	foo(5);
	std::cout << "\n";
	foo(4);
	std::cout << "\n";
	bar(3);
	std::cout << "\n";
}
