class outer
{
private:
	struct inner
	{
		void g() {}
	};

public:
	static inner f() { return inner{}; }
};

int main()
{
	outer::inner n1 = outer::f(); // error: outer::inner is private
	auto n2 = outer::f(); // ok
	n2.g();               // ok
	outer::f().g();       // ok

	using inner = decltype(outer::f()); // create a type alias from the type of expression
	inner{}.g(); // ok
}
