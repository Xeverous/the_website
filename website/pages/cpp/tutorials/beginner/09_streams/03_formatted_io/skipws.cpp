#include <iostream>
#include <sstream>

int main()
{
	const auto text = "a b c d";
	std::istringstream iss;
	char c = '\0';

	iss.str(text);
	iss >> std::skipws; // default behavior (this statement has no effect)
	while (iss >> c) // will stop on reaching end of internal string buffer and set EOF
	{
		std::cout << "[" << c << "], ";
	}

	std::cout << "\n";
	iss.clear(); // clear EOF

	iss.str(text);
	iss >> std::noskipws;
	while (iss >> c)
	{
		std::cout << "[" << c << "], ";
	}
}
