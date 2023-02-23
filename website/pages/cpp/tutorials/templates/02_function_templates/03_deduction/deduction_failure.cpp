#include <vector>

template <typename T, typename U>
void f(T, T, U) {}

template <typename T>
void g1(std::vector<T>) {}

template <typename T>
void g2(std::vector<T>, T) {}

int main()
{
	f(1, 2, 3);   // ok: T deduced as int, U deduced as int
	f(1, 2, 3.0); // ok: T deduces as int, U deduced as double

	// error: conflicting deductions
	// argument 1 deduced T as int,
	// argument 2 deduced T as double
	// argument 3 deduced U as int
	// f(1, 2.0, 3);

	// error: can not deduce T (not std::initializer_list)
	// g1({1, 2, 3});

	// argument 1 can not deduce T
	// argument 2 deduces T as int
	g2({1, 2, 3}, 4); // ok
}
