const int& r = 42; // ok: const reference extents the lifetime of a temporary

std::function<const int&()> f = []{ return 42; };
const int& rf = f(); // undefined behavior: dangling reference
