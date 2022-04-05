struct bar {
	static int x;
};

struct baz {
	static int y;
};

// one translation unit
int bar::x = 1;

// other translation unit
int baz::y = bar::x;
