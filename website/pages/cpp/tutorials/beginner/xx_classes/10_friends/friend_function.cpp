#include <iostream>

class foo
{
private:
	int x = 1;

	// this is not a member function but a friend function declaration
	friend void func(foo f);
};

void func(foo f) // friends can access private and protected members
{
	std::cout << "f.x = " << f.x << "\n";
}

int main()
{
	foo f;
	func(f);
}
