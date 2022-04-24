#include <iostream>

class A
{
public:
	virtual void f() { std::cout << "A::f\n"; }
};

class B: public A
{
public:
	B() { f(); }

	void f() override { std::cout << "B::f\n"; }
};

class C: public B
{
public:
	void f() override { std::cout << "C::f\n"; }
};

int main()
{
	C c;
}
