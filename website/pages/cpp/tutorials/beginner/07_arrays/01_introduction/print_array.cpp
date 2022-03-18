#include <iostream>

// in C++17 you can remove this and use std::size
template <typename T, int N>
constexpr int size(const T (&)[N]) noexcept
{
	return N;
}

void print(const int* arr, int size)
{
	for (int i = 0; i < size; ++i)
		std::cout << arr[i] << ", ";

	std::cout << "\n";
}

int main()
{
	int arr1[] = {1, 2, 3};
	int arr2[] = {3, 1, 3, 3, 7};

	print(arr1, size(arr1));
	print(arr2, size(arr2));
}
