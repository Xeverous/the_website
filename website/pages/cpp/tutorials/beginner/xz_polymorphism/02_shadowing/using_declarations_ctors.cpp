class base
{
public:
	base(int x, int y, int z);
	base(double v);
};

class derived: public base
{
public:
	// works like
	// derived(int x, int y, int z) : base(x, y, z) {}
	// derived(double v) : base(v) {}
	using base::base;

private:
	std::string str; // will use string's default constructor
	int n = 0;       // has explicitly specified initializer
};
