#include <functional>
#include <iostream>

int f1(int x, int y)
{
	return x * y;
}

struct foo
{
	int operator()(int x, int y) const
	{
		return x * y;
	}
};

struct bar
{
	int func(int x, int y) const
	{
		return x * y + z;
	}

	int z;
};

int main()
{
	// from a free function
	std::function<int(int, int)> func = f1;
	std::cout << func(2, 3) << "\n";

	// from a lambda expression
	func = [](int x, int y) { return x * y; };
	std::cout << func(2, 3) << "\n";

	// from a type with overloaded operator()
	func = foo{};
	std::cout << func(2, 3) << "\n";

	// from a class member function
	// member functions need an object to work on, thus &b
	bar b{4};
	func = std::bind(&bar::func, &b, 2, 3);
	std::cout << func(2, 3) << "\n";
	// this example could also use a capturing lambda
}
