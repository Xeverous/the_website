#include <iostream>

template <typename T, int N>
constexpr int size(const T (&)[N]) noexcept
{
	return N;
}

void copy(const int* input, int* output, int size)
{

}

void reverse(int* arr, int size)
{

}

bool compare(const int* lhs_arr, int lhs_size, const int* rhs_arr, int rhs_size)
{

}

int main()
{
	int arr1[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
	constexpr int sz = size(arr1);
	int arr2[sz] = {};

	copy(arr1, arr2, sz);
	reverse(arr2);
	reverse(arr2);
	std::cout << std::boolalpha << compare(arr1, sz, arr2, sz);
}
