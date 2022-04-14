std::ostream& operator<<(std::ostream& os, fraction fr)
{
	return std::cout << fr.numerator() << "/" << fr.denominator();
}
