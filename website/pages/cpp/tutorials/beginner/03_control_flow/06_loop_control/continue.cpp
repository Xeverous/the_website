#include <iostream>

int main()
{
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == j)
				continue;

			std::cout << j << "-" << i << ", ";
		}
	}
}
