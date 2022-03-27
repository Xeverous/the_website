namespace foo { void f1(); }

// namespaces can be opened multiple times, potentially in different files
namespace foo { void f2(); }

// namespaces can be nested and entities can appear at any level
namespace bar {
	void f3();

	namespace foo { // bar::foo is not the same as foo
		void f4();

		namespace baz {
			void f5();
		}

		void f6();
	}
}

// definitions of entities can appear in another namespace definition...
namespace foo { void f1() {} }
// ...or use qualified name
void foo::f2() {}

// inside a namespace, enclosing namespace names can be skipped
// this applies to any code that uses entities from enclosed namespace
namespace bar {
	void f3() {}
	void foo::f4() {}      // no need to write bar::foo::f4
	void foo::baz::f5() {} // no need to write bar::foo::baz::f5
}

// out-of-namespace definitions and redeclarations can not appear
// in a namespace that does not enclose original declaration
namespace xyz {
	// error: xyz::bar::foo::f6 does not exist
	// this syntax (qualified-id) can not be used to declare new entities
	// void bar::foo::f6() {}
}

// :: can be used before the name to refer to shadowed entity
void f();
namespace abc {
	void f() // hides (shadows) global f
	{
		::f(); // ok: calls ::f (not a recursion)
	}
}

// it's possible to create namespace aliases
namespace abc {
	namespace bfb = ::bar::foo::baz;
}

void f7()
{
	abc::bfb::f5(); // ok: calls bar::foo::baz::f5
}
