class foo
{
public:
	struct quux { /* ... */ };
	int pub() const;
private:
	int priv() const;
};

class bar
{
	// foo's default constructor (implicitly defined) can access all bar's members
	friend foo::foo();

	friend foo::quux; // ok: all code of foo::quux can access all bar's members

	friend int foo::pub() const;  // ok: foo::pub can access all bar's members
	friend int foo::priv() const; // error: foo::priv is private (not accessible in this context)
};
