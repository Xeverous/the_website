#include <optional>
#include <limits>

std::optional<int> safe_divide(int x, int y)
{
	if (y == 0)
		return std::nullopt; // return {}; works too

	if (x == std::numeric_limits<int>::min() && y == -1)
		return std::nullopt; // return {}; works too

	return x / y;
}
