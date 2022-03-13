#define COMPLEX_MACRO(param) \
	do { \
		f1(param); \
		f2(param); \
		f3(param); \
	} while (false)

// sample usage - looks like a single statement
COMPLEX_MACRO(value); // the ; completes the loop syntax
