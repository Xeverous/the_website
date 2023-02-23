#include <iostream>

template <typename T>
const T& min(const T& x, const T& y)
{
	if (y < x)
		return y;
	else
		return x;
}

template <typename U, typename T>
U convert_to(T value)
{
	return static_cast<U>(value);
}

int main()
{
	// min(1, 2.0); // error: conflicting deductions for T
	min<double>(1, 2.0); // ok: T = double

	// U is explicitly specified as unsigned short
	// T is deduced from the argument as int
	std::cout << convert_to<unsigned short>(-1); // ok
}
