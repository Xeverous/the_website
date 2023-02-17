// foo.hpp
struct foo
{
	foo(int x): x(x) {}

	int x = 0;
	static int s; // static member
};

// foo.cpp
int foo::s = 1; // initialization of static member

// main.cpp
#include <iostream>
#include <memory>

int main()
{
	foo f1(10);
	foo f2(20);

	// static members are shared across all instances
	std::cout << "f1.s = " << f1.s << "\n";
	std::cout << "f2.s = " << f2.s << "\n";

	++f1.s;

	std::cout << "f1.s = " << f1.s << "\n";
	std::cout << "f2.s = " << f2.s << "\n";

	// it's actually the same object
	std::cout << "address of f1.s = " << std::addressof(f1.s) << "\n";
	std::cout << "address of f2.s = " << std::addressof(f2.s) << "\n";

	// static members are not a part of the object
	// the class has 2 ints but only 1 contributes to the size
	std::cout << "sizeof(int) = " << sizeof(int) << "\n";
	std::cout << "sizeof(foo) = " << sizeof(foo) << "\n";

	// you actually don't need any object to access static members
	++foo::s;
	std::cout << "foo::s = " << foo::s << "\n";
}
