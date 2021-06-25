#include <iostream>
#include <bitset>

int main()
{
	unsigned a = 0b01001100;

	std::cout << " a: " << std::bitset<8>(a)  << "\n";
	std::cout << "~a: " << std::bitset<8>(~a) << "\n";
}
