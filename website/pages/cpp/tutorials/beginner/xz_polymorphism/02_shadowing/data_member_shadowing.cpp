struct base
{
	int x = 0;
};

struct derived: base
{
	int x = 1; // shadows base::x

	void print() const;
};

void derived::print() const
{
	std::cout << "derived::x: " << x << "\n";
	std::cout << "base::x: " << base::x << "\n";
}

int main()
{
	derived d;
	d.print();
	d.x *= 10;
	d.base::x *= 10;
	d.print();
}
