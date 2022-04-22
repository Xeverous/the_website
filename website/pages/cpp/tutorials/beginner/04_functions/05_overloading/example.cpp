#include <iostream>

void divide(int a, int b)
{
	if (b == 0)
	{
		std::cout << "can not divide by 0\n\n";
		return;
	}

	std::cout << "quotient: " << a / b << "\n";
	std::cout << "remainder: " << a % b << "\n\n";
}

void divide(double a, double b)
{
	std::cout << "quotient: " << a / b << "\n\n";
}

int main()
{
	divide(16, 7);
	divide(13, 0);
	divide(16.0, 7.0);
	divide(13.0, 0.0);
}
