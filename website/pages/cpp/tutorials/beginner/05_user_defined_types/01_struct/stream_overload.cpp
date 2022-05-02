// std::cout is a global object of type std::ostream
std::ostream& operator<<(std::ostream& stream, point p)
{
	return stream << "(" << p.x << ", " << p.y << ")\n";
}
