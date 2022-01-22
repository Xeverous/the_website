#include <iostream>

int index_2d_to_1d(int y, int x, int size_x)
{
	return size_x * y + x;
}

int main()
{
	constexpr int size_y = 5;
	constexpr int size_x = 10;
	constexpr int size_total = size_x * size_y;

	int arr[size_total] = {};

	// do not change these loops, they fill the array
	// with data that represents its order in memory
	// (these could also be written using 1D index)
	for (int y = 0; y < size_y; ++y)
		for (int x = 0; x < size_x; ++x)
			arr[index_2d_to_1d(y, x, size_x)] = size_x * y + x;

	for (int i = 0; i < size_total; ++i)
	{
		if (i % size_x == 0)
			std::cout << "\n";

		std::cout << arr[i] << ", ";
	}
}
