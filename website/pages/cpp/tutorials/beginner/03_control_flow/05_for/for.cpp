#include <iostream>

int main()
{
	{
		int i = 0;
		while (i < 10)
			std::cout << i++ << ", ";
	}

	std::cout << "\n";

	for (int i = 0; i < 10; ++i)
		std::cout << i << ", ";
}
