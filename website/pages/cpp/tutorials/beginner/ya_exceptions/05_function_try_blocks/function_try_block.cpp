#include <cmath>
#include <string>
#include <iostream>

int func(std::string number) try
{
	// may throw std::invalid_argument and std::out_of_range
	int n = std::stoi(number);

	if (n < 0)
		throw std::runtime_error("value should be non-negative");

	return std::sqrt(n);
}
catch (const std::runtime_error& e)
{
	std::cout << "error: " << e.what() << "\n";
	return 0;
}
catch (...)
{
	return 0;
}
