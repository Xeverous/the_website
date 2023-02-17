struct foo
{
	struct bar
	{
		void f1() {}
		void f2();
	};

	struct baz; // forward declaration
};

struct foo::baz
{
	void g1() {}
	void g2();
};

void foo::bar::f2() {}
void foo::baz::g2() {}
