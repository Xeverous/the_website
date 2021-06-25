#include <iostream>
#include <cstdint> // for fixed-width type aliases

int main()
{
	std::uint16_t x = 65535u;
	std::cout << "before overflow: " << x << "\n";

	x += 3;
	std::cout << "after overflow: " << x << "\n";

	x -= 3;
	std::cout << "after another overflow: " << x << "\n";
}
