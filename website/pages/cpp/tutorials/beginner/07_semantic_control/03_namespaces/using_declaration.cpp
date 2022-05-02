void f();

namespace abc
{
	void g1();
	void g2();
}

namespace xyz
{
	using ::f;
	using abc::g1;
}

void h()
{
	xyz::f();  // calls ::f
	xyz::g1(); // calls abc::g1

	using abc::g2;
	g2(); // calls abc::g2
}
