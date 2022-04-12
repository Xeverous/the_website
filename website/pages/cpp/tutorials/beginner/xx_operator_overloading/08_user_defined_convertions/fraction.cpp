// all code inside fraction class

explicit operator float() const
{
	return static_cast<float>(numerator()) / denominator();
}

explicit operator double() const
{
	return static_cast<double>(numerator()) / denominator();
}

explicit operator long double() const
{
	return static_cast<long double>(numerator()) / denominator();
}

explicit operator bool() const
{
	return numerator() != 0;
}

// not needed in C++11 and later
bool operator!() const
{
	return !operator bool();
}
