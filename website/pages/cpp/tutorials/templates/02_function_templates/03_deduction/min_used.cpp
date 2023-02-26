#include <iostream>

template <typename T>
const T& min(const T& x, const T& y)
{
	if (y < x)
		return y;
	else
		return x;
}

int main()
{
	std::cout << ::min(2, 1)        << "\n"; // deduces T as int
	std::cout << ::min(1.618, 3.14) << "\n"; // deduces T as double
	std::cout << ::min('a', 'b')    << "\n"; // deduces T as char
}
