double min(double x, double y)
{
	if (y < x)
		return y;
	else
		return x;
}

const std::string& min(const std::string& x, const std::string& y)
{
	if (y < x)
		return y;
	else
		return x;
}
