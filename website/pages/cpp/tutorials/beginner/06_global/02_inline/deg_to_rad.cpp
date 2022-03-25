constexpr double pi = 3.141592653589793238;

// 360 degrees = 2π radians
inline double deg_to_rad(double deg)
{
	return deg * (pi / 180.0);
}

inline double rad_to_deg(double rad)
{
	return rad * (180.0 / pi);
}
