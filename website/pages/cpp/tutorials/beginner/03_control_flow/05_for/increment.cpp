#include <iostream>

int main()
{
	int x = 10;
	int y = x;

	std::cout << "before: " << x << "\n";
	std::cout << "during: " << ++x << "\n";
	std::cout << "after : " << x << "\n\n";

	std::cout << "before: " << y << "\n";
	std::cout << "during: " << y++ << "\n";
	std::cout << "after : " << y << "\n\n";
}
