#include <iostream>
#include <bitset>

int main()
{
	unsigned a = 0b11101001;
	unsigned b = 0b01010101;

	std::cout << "a      : " << std::bitset<8>(a) << "\n";
	std::cout << "b      : " << std::bitset<8>(b) << "\n";

	std::cout << "a AND b: " << std::bitset<8>(a & b) << "\n";
	std::cout << "a  OR b: " << std::bitset<8>(a | b) << "\n";
	std::cout << "a XOR b: " << std::bitset<8>(a ^ b) << "\n";
}
