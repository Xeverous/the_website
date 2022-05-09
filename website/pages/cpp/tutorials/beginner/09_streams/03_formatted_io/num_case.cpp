#include <iostream>

int main()
{
	std::cout << std::hex << std::showbase;
	std::cout << std::uppercase   << 0xdeadbeef << " " << 123456789.0 << "\n";
	std::cout << std::nouppercase << 0xdeadbeef << " " << 123456789.0 << "\n"; // default
}
