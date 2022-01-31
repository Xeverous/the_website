#include <array>
#include <iostream>

int main()
{
	std::array<int, 5> arr1 = {1, 2, 3, 4, 5};

	// array assignment works
	auto arr2 = arr1;

	// comparison checks all elements
	std::cout << (arr1 == arr2) << "\n"; // 1

	// indexing works the same way
	arr2[0] = 2;
	std::cout << (arr1 == arr2) << "\n"; // 0

	// std::array offers additional functionalities:

	// member functions
	std::cout << arr2.size() << "\n"; // 5

	// ranged loops
	for (int value : arr2)
		std::cout << value << " ";
}
