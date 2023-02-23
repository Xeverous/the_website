#include <initializer_list>

template <typename T>
void f1(std::initializer_list<T>) {}

template <typename T>
void f2(T) {}

int main()
{
	// copy-list-initialization
	auto a1 = {1, 2, 3}; // auto = std::initializer_list<int>

	// direct-list-initialization
	// auto a2{1, 2, 3}; // error: not allowed with muliple parameters and deduction
	auto a3{1};          // auto = int
	// TODO when was N3922 introduced? C++11? C++17?

	f1({1, 2, 3});    // T = int
	// f2({1, 2, 3}); // error: can not deduce from braced-init-list
}
