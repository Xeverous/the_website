#include <iostream>

struct A    { virtual void f()  { std::cout << "A::f\n"; } };
struct B: A { void f() override { std::cout << "B::f\n"; } };
struct C: A { void f() override { std::cout << "C::f\n"; } };
struct D: B, C {};

int main()
{
	D d;

	// error: D::f is ambiguous
	// d.f();

	// error: A is an ambiguous base of D
	// (there are 2 A objects within D, this cast is unclear)
	// A& ra = d;

	// solution: add an intermediate cast
	// this informs the compiler which graph edge to follow
	// cast from D to B/C is not ambiguous
	// cast from B/C to A is not ambiguous
	A& rab = static_cast<B&>(d);
	A& rac = static_cast<C&>(d);

	// 2 distinct A objects, each with different overrider
	rab.f();
	rac.f();
}
