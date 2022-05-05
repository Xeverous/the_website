#include <iostream>

int main()
{
	std::cout << std::hex << std::showbase;
	std::cout << std::uppercase   << 0xdeadbeef << "\n";
	std::cout << std::nouppercase << 0xdeadbeef << "\n"; // default
}
