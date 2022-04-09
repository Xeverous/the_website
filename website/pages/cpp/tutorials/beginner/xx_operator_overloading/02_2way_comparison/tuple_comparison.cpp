#include <tuple>

struct package
{
	int rack;
	int shelf;
	int position;
};

// bug-prone manual implementation
bool operator<(package lhs, package rhs)
{
	if (lhs.rack != rhs.rack)
		return lhs.rack < rhs.rack;

	if (lhs.shelf != rhs.shelf)
		return lhs.shelf < rhs.shelf;

	return lhs.position < rhs.position;
}

// same behavior, but much cleaner
bool operator<(package lhs, package rhs)
{
	// orders elements by rack first, then by shelf, then by position
	// this will call bool operator<(std::tuple<int&, int&, int&>, std::tuple<int&, int&, int&>)
	return std::tie(lhs.rack, lhs.shelf, lhs.position)
	     < std::tie(rhs.rack, rhs.shelf, rhs.position);
}
