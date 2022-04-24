#include <iostream>
#include <string>
#include <typeinfo> // for std::bad_cast

enum class animal_type_info { cat, dog };

class animal
{
public:
	virtual std::string sound() const = 0;
	virtual animal_type_info type_info() const = 0;
};

class cat: public animal
{
public:
	std::string sound() const override { return "meow"; }
	animal_type_info type_info() const override { return animal_type_info::cat; }
};

class dog: public animal
{
public:
	std::string sound() const override { return "whoof"; }
	animal_type_info type_info() const override { return animal_type_info::dog; }
};

void test(animal& a)
{
	// A: static downcast
	// because invalid static downcasts are UB, we need to check actual type
	if (a.type_info() == animal_type_info::cat)
	{
		auto& c = static_cast<cat&>(a);
	}

	// B: dynamic downcast on pointers
	// since C++17 it can be written using 2-statement syntax:
	// if (auto ptr = dynamic_cast<cat*>(&a); ptr != nullptr)
	auto ptr = dynamic_cast<cat*>(&a);
	if (ptr != nullptr)
	{
		cat& c = *ptr;
	}

	// C: dynamic downcast on references
	try
	{
		auto& c = dynamic_cast<cat&>(a);
	}
	catch (const std::bad_cast& /* e */)
	{
		// object is not a cat
	}
}

int main()
{
	cat c;
	test(c);
}
