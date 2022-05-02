// inside the library
#define LIB_VERSION_ENCODE(x, y, z) (10000 * x + 100 * y + z)
#define LIB_VERSION LIB_VERSION_ENCODE(2, 1, 3)

// some code that uses the library
#include <lib/version.hpp>
#if LIB_VERSION >= LIB_VERSION_ENCODE(2, 0, 0)
	// [...] code that uses newer approach
#elif LIB_VERSION >= LIB_VERSION_ENCODE(1, 6, 11)
	// [...] code that uses older approach
#else
	#error LIB_VERSION is too low!
#endif
