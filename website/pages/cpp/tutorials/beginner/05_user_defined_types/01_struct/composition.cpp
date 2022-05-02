#include <iostream>

struct point
{
	int x = 0;
	int y = 0;
};

struct triangle
{
	point p1;
	point p2;
	point p3;
};

struct circle
{
	// initializers already specified inside
	point origin;
	// built-in types need initializers
	int radius = 0;
};

void print(const char* name, point p)
{
	std::cout << name << " = (" << p.x << ", " << p.y << ")\n";
}

void print(const char* name, triangle t)
{
	std::cout << name << " = {\n";
	print("p1", t.p1);
	print("p2", t.p2);
	print("p3", t.p3);
	std::cout << "}\n";
}

int main()
{
	triangle t1;
	t1.p1.x = 1;
	t1.p1.y = 2;
	t1.p2.x = -2;
	t1.p2.y = -1;
	t1.p3.x = 3;
	t1.p3.y = 3;

	// equivalent aggregate initialization (C++14)
	triangle t2{{1, 2}, {-2, -1}, {3, 3}};

	print("t1", t1);
	print("t2", t2);
}
