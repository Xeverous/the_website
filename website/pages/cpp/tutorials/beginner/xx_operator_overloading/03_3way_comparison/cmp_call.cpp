const auto cmp = x <=> y; // cmp will be std::*_ordering
if (cmp < 0)
	std::cout << "x < y";
else if (cmp > 0)
	std::cout << "x > y";
else
	std::cout << "x == y";
