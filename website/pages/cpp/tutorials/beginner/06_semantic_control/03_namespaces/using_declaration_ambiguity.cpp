namespace abc
{
	void f(int);
	void f(double);

	void g(int);
}

namespace xyz
{
	void f(int);
	void f(double);
	void f(char);
}

void g();
// using abc::g; // error: g already in this scope

// no error even though some overloads are identical
using abc::f;
using xyz::f;

// void f(int); // error: conflicts with abc::f(int) and xyz::f(int)

void h()
{
	f('h'); // calls xyz::f(char)
	f(1.0); // error: ambiguity between abc::f(double) and xyz::f(double)
}
