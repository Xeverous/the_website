#include <iostream>

class foo
{
private:
	int x = 1;

	friend void func(foo f) // implicitly inline
	{
		std::cout << "f.x = " << f.x << "\n";
	}
};

int main()
{
	foo f;
	func(f);
}
