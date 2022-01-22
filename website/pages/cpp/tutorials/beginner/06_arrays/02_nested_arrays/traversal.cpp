#include <iostream>

int main()
{
	constexpr int size_y = 5;
	constexpr int size_x = 10;

	int arr[size_y][size_x] = {};

	// do not change these loops, they fill the array
	// with data that represents its order in memory
	for (int y = 0; y < size_y; ++y)
		for (int x = 0; x < size_x; ++x)
			arr[y][x] = size_x * y + x;


	std::cout << "proper multidimentional array loop:\n";
	for (int y = 0; y < size_y; ++y)
	{
		for (int x = 0; x < size_x; ++x)
			std::cout << arr[y][x] << ", ";

		std::cout << "\n";
	}

	std::cout << "badly written multidimentional array loop:\n";
	for (int x = 0; x < size_x; ++x)
	{
		for (int y = 0; y < size_y; ++y)
			std::cout << arr[y][x] << ", ";

		std::cout << "\n";
	}
}
