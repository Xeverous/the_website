// C approach
#define FOOBAR_SIZE 1024
char foobar[FOOBAR_SIZE]; // ok: size is a constant expression
for (int i = 0; i < FOOBAR_SIZE; ++i)
	// ... something with foobar[i]

// C++ approach (after C++11 would use constexpr)
const int foobar_size = 1024; // in C not treated as constant expression
char foobar[foobar_size]; // this would not be valid in C
for (int i = 0; i < foobar_size; ++i)
	// ... something with foobar[i]
