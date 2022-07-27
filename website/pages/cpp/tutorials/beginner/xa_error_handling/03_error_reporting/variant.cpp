#include <system_error>
#include <variant>
#include <limits>

std::variant<int, std::errc> safe_divide(int x, int y)
{
	if (y == 0)
		return std::errc::invalid_argument;

	if (x == std::numeric_limits<int>::min() && y == -1)
		return std::errc::result_out_of_range;

	return x / y;
}
