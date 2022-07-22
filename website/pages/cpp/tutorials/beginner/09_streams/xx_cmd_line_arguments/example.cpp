#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "argument count: " << argc << "\n";
	std::cout << "argument vector:\n";

	for (int i = 0; i < argc; ++i)
		std::cout << i << ": " << argv[i] << "\n";
}
