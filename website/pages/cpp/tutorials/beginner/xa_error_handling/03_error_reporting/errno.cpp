#include <cerrno>
#include <limits>

int safe_divide(int x, int y)
{
	if (y == 0)
	{
		// integer division by 0 is UB
		// such operation has no mathematical sense, thus "invalid argument"
		errno = EINVAL;
		return 0;
	}

	if (x == std::numeric_limits<int>::min() && y == -1)
	{
		// negation of lowest negative value is larger than highest possible positive value
		errno = ERANGE;
		return 0;
	}

	return x / y;
}
