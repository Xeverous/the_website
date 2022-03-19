// main.cpp
#include "greet.hpp"
#include <iostream>

int main()
{
	greet();
}

// greet.hpp
#pragma once

static void greet();

// greet.cpp
#include "greet.hpp"
#include <iostream>

static void greet()
{
	std::cout << "hello, world\n";
}
