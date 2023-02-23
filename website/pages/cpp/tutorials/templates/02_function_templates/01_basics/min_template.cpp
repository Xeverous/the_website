template <typename T>
const T& min(const T& x, const T& y)
{
	if (y < x)
		return y;
	else
		return x;
}
