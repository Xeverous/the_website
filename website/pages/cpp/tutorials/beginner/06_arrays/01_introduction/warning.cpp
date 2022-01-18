#include <iostream>

int main()
{
	int arr[] = {1, 2, 3};

	// auto deduced to std::size_t
	// std::size(arr) would deduce auto as std::size_t too
	const auto sz = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < sz; ++i)
		std::cout << arr[i];
}
