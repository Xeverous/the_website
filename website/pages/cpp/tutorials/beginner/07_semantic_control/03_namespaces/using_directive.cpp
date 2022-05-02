namespace abc
{
	int i = 1;
	void f(char);
}

namespace foo
{
	int i = 2;
	int j = 3;

	namespace bar
	{
		namespace baz
		{
			// names from abc injected into global namespace
			// (including any names later declared in abc)
			using namespace abc;

			int j = 4;
			int k = 5;
			int a = i; // ok: foo::i hides abc::i
		}

		// names from baz injected into bar
		// names from abc injected into global namespace (using namespace is transitive)
		using namespace baz;

		int l = k; // ok, uses baz::k
		int k = 6; // ok, no name conflict
		int m = k; // error: bar::k or baz::k?
		int n = i; // ok: foo::i hides abc::i
		int o = j; // ok: baz::j hides foo::j
	}
}

using namespace abc;

namespace xyz
{
	int e = 7;
	void f(int);
}

namespace abc
{
	int d = 8;
	using namespace xyz;
	void f(int);
}

int d = 9;

void func()
{
	++d;      // error: ::d or abc::d?
	++::d;    // ok
	++abc::d; // ok
	++e;      // ok (using namespace is transitive)

	f(1);     // error: xyz::f(int) or abc::f(int)?
	f('a');   // ok: abc::f(char)
}
