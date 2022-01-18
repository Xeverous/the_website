#include <iostream>

int main()
{
	constexpr int sz = 10;
	int powers[sz] = {};

	// the most idiomatic and classic loop that handles an array
	// in almost all situations, i should not be modified inside loop body
	for (int i = 0; i < sz; ++i)
	{
		// reminder: << here is bit shift operator
		// shifting 1 will create different powers of 2
		powers[i] = 1 << i;
	}

	for (int i = 0; i < sz; ++i)
		std::cout << powers[i] << ", ";
}
