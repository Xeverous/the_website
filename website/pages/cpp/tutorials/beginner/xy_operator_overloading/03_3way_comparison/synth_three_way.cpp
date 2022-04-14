#include <compare>
#include <type_traits>

struct synth_three_way_t
{
	template <typename T, std::totally_ordered_with<T> U>
	constexpr auto operator()(const T& lhs, const U& rhs) const
	{
		if constexpr (std::three_way_comparable_with<T, U>)
		{
			return lhs <=> rhs;
		}
		else
		{
			// Jonathan Müller used strong ordering here
			// I don't think we can assume that for arbitrary T and U
			if (lhs == rhs)
				return std::weak_ordering::equivalent;
			else if (lhs < rhs)
				return std::weak_ordering::less;
			else
				return std::weak_ordering::greater;
		}
	}
};
inline constexpr synth_three_way_t synth_three_way;

template <typename T, typename U = T>
using synth_three_way_category
	= decltype(synth_three_way(std::declval<const T&>(), std::declval<const U&>()));
