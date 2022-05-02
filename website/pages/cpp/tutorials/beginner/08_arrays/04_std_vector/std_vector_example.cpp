#include <iostream>
#include <vector>

int main()
{
	// note that there is no size parameter
	std::vector<int> v = {1, 2, 3};

	for (int i = 0; i < 4; ++i)
		v.push_back(i * 10);

	for (int x : v)
		std::cout << x << ", ";

	std::cout << "\nsize: " << v.size() << "\n";
	std::cout << "capacity: " << v.capacity() << "\n";
}
