#include <iostream>

int main()
{
	int x = 22;
	int y = 5;

	int quotient = x / y;
	int remainder = x % y;
	std::cout << "quotient: " << quotient << "\nremainder: " << remainder << "\n";

	// this should always print x
	std::cout << "reversed operation: " << quotient * y + remainder << "\n";
}
