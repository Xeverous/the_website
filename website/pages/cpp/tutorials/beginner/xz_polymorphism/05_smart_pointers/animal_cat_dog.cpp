#include <iostream>
#include <string>
#include <vector>
#include <memory>

class animal
{
public:
	virtual ~animal() = default;
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
	std::cout << a.sound() << "\n";
}

int main()
{
	std::vector<std::unique_ptr<animal>> v;
	v.push_back(std::make_unique<cat>());
	v.push_back(std::make_unique<dog>());

	for (const auto& ptr : v)
		print_sound(*ptr);
}
