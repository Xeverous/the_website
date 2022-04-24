#include <iostream>

struct base { char b; };
struct derived: base { char d; };

int main()
{
	derived d1{{'a'}, 'b'};
	derived d2{{'x'}, 'y'};

	base& b_ref = d1;
	b_ref = d2;

	std::cout << "d1.b: " << d1.b << "\nd1.d: " << d1.d << "\n";
}
