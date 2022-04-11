// (all inside class body)

bool operator==(fraction rhs) const
{
	if (denominator() == rhs.denominator())
		return numerator() == rhs.numerator();

	return numerator() * rhs.denominator() == rhs.numerator() * denominator();
}

std::weak_ordering operator<=>(fraction rhs) const
{
	if (denominator() == rhs.denominator())
	{
		if (denominator() > 0)
			return numerator() <=> rhs.numerator();
		else
			return rhs.numerator() <=> numerator();
	}

	const auto new_lhs_numerator = numerator() * rhs.denominator();
	const auto new_rhs_numerator = rhs.numerator() * denominator();

	if ((denominator() > 0) == (rhs.denominator() > 0))
		return new_lhs_numerator <=> new_rhs_numerator;
	else
		return new_rhs_numerator <=> new_lhs_numerator;
}
