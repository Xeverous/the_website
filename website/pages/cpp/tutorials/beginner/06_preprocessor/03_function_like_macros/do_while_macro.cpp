#define COMPLEX_MACRO(param) \
	do { \
		f1(param); \
		f2(param); \
		f3(param); \
	} while (false)

// sample usage - looks like a single statement
if (some_condition)
	COMPLEX_MACRO(some_value); // the ; completes the loop syntax
