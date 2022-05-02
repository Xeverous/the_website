#include <iostream>

struct point
{
	int x = 0;
	int y = 0;
};

int main()
{
	point p1;
	point p2{2, 2};

	std::cout << "p1 = (" << p1.x << ", " << p1.y << ")\n"
	          << "p2 = (" << p2.x << ", " << p2.y << ")\n";
}
