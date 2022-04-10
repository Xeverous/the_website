// as member functions (code inside class definition)
fraction operator+() const
{
	return *this;
}

fraction operator-() const
{
	return {-numerator(), denominator()};
}

// as free functions
fraction operator+(fraction rhs)
{
	return rhs;
}

fraction operator-(fraction rhs)
{
	return {-rhs.numerator(), rhs.denominator()};
}
