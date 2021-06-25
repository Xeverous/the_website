#include <iostream>
#include <bitset>

int main()
{
	unsigned x = 0b01001100;

	std::cout << " x: " << std::bitset<8>(x)  << "\n";
	std::cout << "~x: " << std::bitset<8>(~x) << "\n";
}
