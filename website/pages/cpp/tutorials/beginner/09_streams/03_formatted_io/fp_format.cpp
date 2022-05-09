#include <iostream>

int main()
{
	std::cout << "0.001 in fixed:      " << std::fixed        << 0.001 << "\n"; // ignores showpoint
	std::cout << "0.001 in scientific: " << std::scientific   << 0.001 << "\n";
	std::cout << "0.001 in hexfloat:   " << std::hexfloat     << 0.001 << "\n"; // ignores precision
	std::cout << "0.001 in default:    " << std::defaultfloat << 0.001 << "\n"; // this is the default

	std::cout << "\n";

	std::cout << " 1000 in fixed:      " << std::fixed        << 1000.0 << "\n";
	std::cout << " 1000 in scientific: " << std::scientific   << 1000.0 << "\n";
	std::cout << " 1000 in hexfloat:   " << std::hexfloat     << 1000.0 << "\n";
	std::cout << " 1000 in default:    " << std::defaultfloat << 1000.0 << "\n";
}
