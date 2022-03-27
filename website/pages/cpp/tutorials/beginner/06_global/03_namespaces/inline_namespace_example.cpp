namespace foo {
	inline namespace bar {
		void f();

		inline namespace baz {
			void g();
		}
	}
}

void func()
{
	// namespace names can be specified explicitly
	foo::bar::f();
	foo::bar::baz::g();

	// namespace names can have inline namespaces ommitted
	foo::f();
	foo::g();
}
