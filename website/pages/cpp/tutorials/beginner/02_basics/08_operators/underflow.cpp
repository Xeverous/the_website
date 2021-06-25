#include <iostream>

int main()
{
	auto x = 1.0f;

	while (x != 0)
	{
		std::cout << x << "\n";
		x /= 2.0f;
	}

	std::cout << x << "\n";
}
