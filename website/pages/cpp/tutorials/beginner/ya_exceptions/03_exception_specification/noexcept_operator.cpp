#include <iostream>
#include <vector>

int main()
{
	// If executed, the expression in the first noexcept would result in undefined behavior.
	// But because the noexcept operator has unevaluated context, there is no problem.
	std::cout << std::boolalpha; // print true/false instead of 1/0
	std::cout << "Can vector's operator[] throw? " << !noexcept(std::vector<int>()[0]) << '\n';
	std::cout << "Can vector's at function throw? " << !noexcept(std::vector<int>().at(0)) << '\n';
}
