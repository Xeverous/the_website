// functions that convert between degrees and radians (360 degrees == 2π radians)
constexpr double pi = 3.141592653589793;

constexpr double deg_to_rad(double degrees)
{
	return degrees * pi / 180.0;
}

constexpr double rad_to_deg(double radians)
{
	return radians * 180.0 / pi;
}
