#include <iostream>
#include <sstream>

int main()
{
	int x = 0;
	int y = 0;
	std::istringstream iss("10 010");
	// comment/uncomment line below for different parsing behavior
	// iss.setf(std::ios_base::fmtflags(0), std::ios_base::basefield);
	iss >> x >> y;
	//   commented: 10 10 (default state has dec bit on),
	// uncommented: 10 8  (no base bits cause parsing to depend on prefix)
	std::cout << x << " " << y << "\n";
}
