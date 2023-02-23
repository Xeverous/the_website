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
	// const reference extends the lifetime of a temporary
	// but this happens only when the temporary is immediately bound
	// in this case the object created by 2 + 3 is dead after the statement
	// const int& result = min(6, 2 + 3); // undefined behavior: dangling reference
	std::cout << min(6, 2 + 3); // ok
}
