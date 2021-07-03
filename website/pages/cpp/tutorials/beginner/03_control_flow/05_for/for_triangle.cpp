#include <iostream>

int main()
{
	for (int j = 1; j <= 5; ++j)
	{
		// note the comparison between i and j
		for (int i = 1; i <= j; ++i)
			std::cout << i << " ";

		std::cout << "\n";
	}
}
