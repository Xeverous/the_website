#include <memory> // for std::addressof
#include <iostream>

int main()
{
	int arr[3] = {1, 2, 3};

	std::cout << std::addressof(arr) << "\n";
	std::cout << std::addressof(arr[0]) << "\n";
	std::cout << std::addressof(arr[1]) << "\n";
	std::cout << std::addressof(arr[2]) << "\n";
}
