struct A
{
	A(char a = 'a'): a(a) {}
	virtual void f() { std::cout << "A::f\n"; }

	char a;
};

struct B: virtual A
{
	B(): A('b') {}
	void f() override { std::cout << "B::f\n"; }
};

struct C: virtual A
{
	C(): A('c') {}
	void f() override { std::cout << "C::f\n"; }
};

struct D: B, C
{
	// How is A initialized in D::D???
};
