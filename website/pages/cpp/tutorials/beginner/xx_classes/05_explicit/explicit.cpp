struct point
{
	point() = default;
	explicit point(int val)
	: x(val), y(val) {}
	explicit point(int x, int y)
	: x(x), y(y) {}

	int x = 0;
	int y = 0;
};

point make_point(int x, int y)
{
	// return {x, y};   // error: constructor is explicit
	return point{x, y}; // ok
}

int main()
{
	// point p1 = 1;      // error: copy-initialization is not allowed
	point p2(2);          // ok: direct-initialization
	point p3{3, 3};       // ok: direct-list-initialization
	// point p4 = {4, 4}; // error: copy-list-initialization is not allowed
}
