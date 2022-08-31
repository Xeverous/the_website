#include <exception> // std::exception
#include <stdexcept> // more standard library exception classes
#include <iostream>

void foo1() { std::cout << "foo1\n"; }
void foo2() { throw std::runtime_error("foo2() failed"); }
void bar1() { std::cout << "bar1\n"; };
void bar2() { std::cout << "bar2\n"; };

void foo()
{
	std::cout << "foo starts\n";
	foo1();
	foo2();
	std::cout << "foo ends\n";
}

void bar()
{
	std::cout << "bar starts\n";
	bar1();
	bar2();
	std::cout << "bar ends\n";
}

void run()
{
	std::cout << "run starts\n";
	foo();
	bar();
	std::cout << "run ends\n";
}

int main()
{
	std::cout << "program start\n";

	try {
		std::cout << "beginning execution\n";
		run();
		std::cout << "ending execution\n";
	}
	catch (const std::exception& e) {
		std::cout << "caught exception with message: " << e.what() << "\n";
	}

	std::cout << "program end\n";
}
