#include <iostream>

int main()
{
	std::cout << std::showpoint   << 1.0 << " " << 12.34 << "\n";
	std::cout << std::noshowpoint << 1.0 << " " << 12.34 << "\n"; // default
}
