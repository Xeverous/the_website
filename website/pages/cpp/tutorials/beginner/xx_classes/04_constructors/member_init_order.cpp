class point
{
private:
	int x;
	int y;
	int z;

public:
	point(int x, int y, int z)
	: x(x), y(y), z(z) {} // ok

	point(int value)
	// x is initialized first, using uninitialized z
	// y is initialized second, using uninitialized z
	// z is initialized third, using parameter value
	// reading uninitialized z => undefined behavior!
	: z(value), x(z), y(z) {}
};
