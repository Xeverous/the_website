#include <vector>
#include <string>
#include <iostream>

template <typename T, typename U = T>
T exchange(T& object, U new_value)
{
	T old_value = object;
	object = new_value;
	return old_value;
}

int main()
{
	// the argument is non-deducible but the default template parameter solves the problem
	std::vector<int> v = {1, 2};
	std::cout << exchange(v, {1, 2, 3, 4}).size() << "\n";

	// the argument is deducible but U (const char*) is different from T (std::string)
	std::string s = "abc";
	std::cout << exchange(s, "xyz") << "\n";
}
