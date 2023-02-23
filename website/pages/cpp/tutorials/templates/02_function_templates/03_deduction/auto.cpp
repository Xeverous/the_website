template <typename T>
void f1(T) {}

template <typename T>
void f2(T&) {}

int main()
{
	const int x = 1;

	auto  a1 = x; // auto =       int, a1 has type       int
	auto& a2 = x; // auto = const int, a2 has type const int&

	f1(x); // T =       int, parameter has type       int
	f2(x); // T = const int, parameter has type const int&
}
