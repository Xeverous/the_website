#include <stdexcept>

class base
{
public:
	base(int x)
	{
		if (x < 0)
			throw std::runtime_error("x can not be negative");
	}
};

class derived : public base
{
public:
	derived(int x) try : base(x)
	{
		// ctor body
	}
	catch (const std::exception& /* e */)
	{
		// ...
	}
	catch (...)
	{
		// ...
	}
};
