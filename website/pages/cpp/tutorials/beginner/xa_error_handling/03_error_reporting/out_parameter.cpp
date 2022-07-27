#include <limits>

// by convention, output parameter should be last
int safe_divide(int x, int y, bool& success)
{
	if (y == 0)
	{
		success = false;
		return 0;
	}

	if (x == std::numeric_limits<int>::min() && y == -1)
	{
		success = false;
		return 0;
	}

	success = true;
	return x / y;
}
