#include <iostream>
#include <functional>

void f(int n1, int n2, int n3, const int& n4, int n5)
{
	std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int main()
{
	using namespace std::placeholders;

	int n = 7;
	auto b = std::bind(f, _2, 42, _1, std::cref(n), n);
	n = 10;
	b(1, 2, 3);

	// same behavior
	n = 7;
	auto l = [ncref = std::cref(n), n = n](auto a, auto b, auto /* unused */) { f(b, 42, a, ncref, n); };
	n = 10;
	l(1, 2, 3);
}
