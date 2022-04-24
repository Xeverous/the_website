#include <iostream>

class base
{
public:
	virtual void f(double)
	{
		std::cout << "base::f\n";
	}
};

class derived: public base
{
public:
	virtual void f(float) // oops, wrong argument type
	{
		std::cout << "derived::f\n";
	}
};

class more_derived: public derived
{
public:
	virtual void f(double)
	{
		std::cout << "more_derived::f\n";
	}
};

void run(base& b)
{
	b.f(1.0);
}

int main()
{
	base b;
	derived d;
	more_derived md;
	run(b);
	run(d);
	run(md);
}
