#include <iostream>
#include <cmath>

int main()
{
	// 1000^1000 is too large to represent - hence infinity
	std::cout << std::pow(1000, 1000) << "\n";
	// logarithms can not accept negative numbers, hence NaN
	std::cout << std::log(-1) << "\n";
}
