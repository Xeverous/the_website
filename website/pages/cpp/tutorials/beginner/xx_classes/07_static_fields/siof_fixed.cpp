struct barz {
	barz(int val): x(val), y(val) {}

	int x;
	int y;
};

struct foo {
	static barz b;
};

barz foo::b(1);
