std::ostream& operator<<(std::ostream& os, const animal& a)
{
	return os << a.sound();
}
