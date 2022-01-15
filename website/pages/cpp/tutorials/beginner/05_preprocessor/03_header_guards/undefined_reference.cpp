// main.cpp
#include "hello.hpp"
#include <iostream>

int main()
{
	write_hello();
	std::cout << " world\n";
}

// hello.hpp
void write_hello();

// hello.cpp
#include "hello.hpp"
#include <iostream>
/*
void write_hello()
{
	std::cout << "hello";
}
*/
