#include <iostream>

class base1
{
public:
	virtual void f() { std::cout << "base1::f\n"; }
};

class base2
{
public:
	virtual void f() { std::cout << "base2::f\n"; }
};

class derived: public base1, public base2
{
public:
	void f() override { std::cout << "derived::f\n"; }
};

int main()
{
	derived d;
	base1& r1 = d;
	base2& r2 = d;
	r1.f();
	r2.f();
}
