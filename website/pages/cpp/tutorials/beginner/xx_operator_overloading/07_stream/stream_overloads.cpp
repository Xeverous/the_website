std::ostream& operator<<(std::ostream& os, fraction fr)
{
	return os << fr.numerator() << "/" << fr.denominator();
}

std::istream& operator>>(std::istream& is, fraction& fr)
{
	// implementations can vary a lot
	// this one works with the output overload but does no error handling
	int value = 0;
	is >> value;
	fr.numerator(value);
	is.ignore(); // ignores next character
	is >> value;
	fr.denominator(value);
	return is;
}
