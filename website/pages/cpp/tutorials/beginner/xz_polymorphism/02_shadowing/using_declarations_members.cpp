class base
{
public:
	void f(int);
	void g(int);

protected:
	int m = 0;
};

class derived: public base
{
public:
	// derived::m is public
	// if base::m was private, this would be rejected
	// (derived can not redefine access if it itself has no access)
	using base::m;

	using base::f;
	void f(long); // does not hide base::f, now there are 2 overloads

	using base::g;
	void g(int); // still hides base::g because this overload is identical
};

void func()
{
	derived d;
	d.m = 2; // ok
	base& b = d;
	b.m = 1; // error: base::m is protected

	d.f(1);  // ok, calls base::f
	d.f(1l); // ok, calls derived::f

	d.g(1); // ok, calls derived::g
	d.base::g(1); // ok, calls base::g
	b.g(1); // ok, calls base::g
}
