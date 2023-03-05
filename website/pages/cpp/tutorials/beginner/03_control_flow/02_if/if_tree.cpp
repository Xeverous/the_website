#include <iostream>

int main()
{
	int x = 6;

	if (x % 2 == 0)
	{
		std::cout << x << " is divisible by 2\n";
	}
	else
	{
		if (x % 3 == 0)
		{
			std::cout << x << " is divisible by 3\n";
		}
		else
		{
			if (x % 5 == 0)
			{
				std::cout << x << " is divisible by 5\n";
			}
			else
			{
				if (x % 7 == 0)
				{
					std::cout << x << " is divisible by 7\n";
				}
				else
				{
					if (x % 11 == 0)
						std::cout << x << " is divisible by 11\n";
				}
			}
		}
	}
}
