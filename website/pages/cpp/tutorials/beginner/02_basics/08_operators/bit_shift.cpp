#include <iostream>
#include <bitset>

int main()
{
	unsigned a = 0b00001100;

	std::cout << "value           : " << std::bitset<8>(a) << "\n";
	std::cout << "shift left  by 4: " << std::bitset<8>(a << 4) << "\n";
	std::cout << "shift left  by 5: " << std::bitset<8>(a << 5) << "\n";
	std::cout << "shift left  by 6: " << std::bitset<8>(a << 6) << "\n";
	std::cout << "shift right by 2: " << std::bitset<8>(a >> 2) << "\n";
	std::cout << "shift right by 3: " << std::bitset<8>(a >> 3) << "\n";
	std::cout << "shift right by 4: " << std::bitset<8>(a >> 4) << "\n";
}
