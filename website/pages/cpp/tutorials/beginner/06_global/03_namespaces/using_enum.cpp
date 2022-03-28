enum class fruit { apple, orange };
enum class color { green, orange, red };

struct boo
{
	using enum fruit;
};

void f()
{
	// ok: auto = fruit
	auto x = boo::orange;
	// also ok, but I wouldn't write such code
	// I guess this syntax is allowed to make writing templates easier
	boo b;
	auto y = b.orange;
}

void g()
{
	using enum fruit; // ok: you can now use apple and orange
	using enum color; // error: fruit::orange and color::orange conflict
}
