#include <tuple>

struct package
{
	int rack;
	int shelf;
	int position;
	// [...] some other members that should not be used in comparison

	auto operator<=>(package rhs) const
	{
		return std::tie(rack, shelf, position)
		   <=> std::tie(rhs.rack, rhs.shelf, rhs.position);
	}
};
