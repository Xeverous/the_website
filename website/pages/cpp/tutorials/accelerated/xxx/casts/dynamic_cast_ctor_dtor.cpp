struct base { virtual ~base() = default; };
struct left : virtual base {};
struct right : virtual base
{
	right(base* b, left* l)
	{
		// casts during construction (see the call in the constructor of derived below)

		// well-defined: right inherits base
		dynamic_cast<right*>(b);

		// right is not derived from left
		// undefined behavior even if the final object inherits right
		dynamic_cast<right*>(l);
	}
};

struct derived : left, right
{
	derived() : left(static_cast<left*>(this), this) {}
};
