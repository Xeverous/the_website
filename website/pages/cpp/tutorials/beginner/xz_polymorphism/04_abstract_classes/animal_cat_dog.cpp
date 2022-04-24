#include <iostream>
#include <string>

class animal
{
public:
	// for historical reasons, there is no "pure" or "abstract" keyword in C++
	// instead, pure virtual functions are denoted with "= 0"
	virtual std::string sound() const = 0;
};

class cat: public animal
{
public:
	std::string sound() const override { return "meow"; }
};

class dog: public animal
{
public:
	std::string sound() const override { return "whoof"; }
};

void print_sound(const animal& a)
{
	std::cout << a.sound() << "\n"; // virtual function call
}

int main()
{
	cat c;
	dog d;
	print_sound(c);
	print_sound(d);
}
