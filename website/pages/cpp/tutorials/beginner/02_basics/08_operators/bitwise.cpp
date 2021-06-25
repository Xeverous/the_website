#include <iostream>
#include <bitset>

int main()
{
	unsigned x = 0b11101001;
	unsigned y = 0b01010101;

	std::cout << "x      : " << std::bitset<8>(x) << "\n";
	std::cout << "y      : " << std::bitset<8>(y) << "\n";

	std::cout << "x AND y: " << std::bitset<8>(x & y) << "\n";
	std::cout << "x  OR y: " << std::bitset<8>(x | y) << "\n";
	std::cout << "x XOR y: " << std::bitset<8>(x ^ y) << "\n";
}
