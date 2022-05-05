#include <iostream>

int main()
{
	std::cout << std::showbase; // enable printing base prefix (0 for octal, 0x for hex)
	std::cout << "in octal       (base  8): " << std::oct << 42 << "\n";
	std::cout << "in decimal     (base 10): " << std::dec << 42 << "\n";
	std::cout << "in hexadecimal (base 16): " << std::hex << 42 << "\n";

	std::cout << "\n";

	std::cout << std::noshowbase; // disable printing base prefix (default)
	std::cout << "in octal       (base  8): " << std::oct << 42 << "\n";
	std::cout << "in decimal     (base 10): " << std::dec << 42 << "\n";
	std::cout << "in hexadecimal (base 16): " << std::hex << 42 << "\n";
}
