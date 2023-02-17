#include <iostream>

class bar
{
public:
	bar() { std::cout << "bar constructor\n"; }
	~bar() { std::cout << "bar destructor\n"; }
};

class baz
{
public:
	baz() { std::cout << "baz constructor\n"; }
	~baz() { std::cout << "baz destructor\n"; }
};

class foo
{
public:
	foo() { std::cout << "foo constructor\n"; }
	~foo() { std::cout << "foo destructor\n"; }

private:
	bar br;
	baz bz;
};

int main()
{
	foo f;
}
