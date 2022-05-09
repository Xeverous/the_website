#include <iostream>
#include <iomanip>

int main()
{
	// adjust left and fill with *
	std::cout << std::left << std::setfill('*');
	for (long i = 1; i < 1000000000; i *= 10)
		std::cout << std::setw(8) << i << "\n";

	std::cout << "\n";

	// adjust right and fill with .
	std::cout << std::right << std::setfill('.');
	for (long i = 1; i < 1000000000; i *= 10)
		std::cout << std::setw(8) << i << "\n";

	std::cout << "\n";

	// use hex base and print prefix, fill with _
	// adjust numbers to the right but other characters to the left
	std::cout << std::hex << std::showbase;
	std::cout << std::internal << std::setfill('_');
	for (long i = 1; i < 1000000000; i *= 10)
		std::cout << std::setw(8) << i << "\n";
}
