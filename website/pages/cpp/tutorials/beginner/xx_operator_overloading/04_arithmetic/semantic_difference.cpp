struct bar {};

struct foo
{
	foo() = default;
	foo(bar) {} // converting constructor

	// (1) member overload, does not allow implicit convertion
	// void operator+() const {}
};

// (2) non-member overload, allows implicit convertion
// void operator+(foo) {}

int main()
{
	+bar{}; // works only with (2)
}
