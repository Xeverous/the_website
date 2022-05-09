#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

int main()
{
	const long double pi = std::acos(-1.0l); // (arc cosine)
	constexpr auto maxp = std::numeric_limits<long double>::digits10 + 1;
	std::cout << "default precision (6): " << pi << "\n"
	          << "std::setprecision(10): " << std::setprecision(10) << pi << "\n"
	          << "max precision        : " << std::setprecision(maxp) << pi << "\n\n";


	// This value will likely not be ideal half due to
	// limited accuracy of floating-point computations.
	const auto almost_half = std::acos(0.0) / pi;

	// Setting precision larger than supported by the underlying
	// floating point type will cause weird output.
	// This is because streams always try to print the value (in decimal)
	// that is closest to the actually stored value (in floating-point).
	// Thus, 0.5 is choosen over 0.4999999999999999 (the first one is more accurate).
	// Once the precision allows to represent this tiny error, output changes.
	for (int i = 6; i < maxp + 3; ++i)
		std::cout << std::setprecision(i) << almost_half << "\n";
}
