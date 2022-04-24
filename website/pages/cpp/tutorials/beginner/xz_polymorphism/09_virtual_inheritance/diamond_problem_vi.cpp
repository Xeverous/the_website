#include <iostream>

struct A            { virtual void f()  { std::cout << "A::f\n"; } };
struct B: virtual A { void f() override { std::cout << "B::f\n"; } };
struct C: virtual A { void f() override { std::cout << "C::f\n"; } };
struct D: B, C
{
	// this is required, otherwise the program is ill-formed
	void f() override { std::cout << "D::f\n"; }
};

int main()
{
	D d;

	d.f(); // ok

	// ok, there is only 1 A within D
	// the cast is not ambiguous
	A& ra = d;
	ra.f();
}
