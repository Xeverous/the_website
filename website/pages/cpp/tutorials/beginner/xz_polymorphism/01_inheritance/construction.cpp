#include <iostream>

class X
{
public:
	X() { std::cout << "X::X()\n"; }
};

class Y: public X
{
public:
	Y() { std::cout << "Y::Y()\n"; }
};

class Z: public Y
{
public:
	Z() { std::cout << "Z::Z()\n"; }
};

class A
{
public:
	A() { std::cout << "A::A()\n"; }

private:
	X x;
};

class B: public A
{
public:
	B() { std::cout << "B::B()\n"; }
};

class C: public B
{
public:
	C() { std::cout << "C::C()\n"; }

private:
	Z z;
};

int main()
{
	C c;
}
