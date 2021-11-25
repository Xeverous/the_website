#include <iostream>

void foo()
{
	std::cout << "foo\n";
}

void bar()
{
	std::cout << "bar start\n";
	foo();
	std::cout << "bar finish\n";
}

void baz()
{
	std::cout << "baz start\n";
	foo();
	std::cout << "baz finish\n";
}

void func()
{
	std::cout << "1\n";
	bar();
	std::cout << "2\n";
	baz();
	std::cout << "3\n";
}

int main()
{
	func();
}
