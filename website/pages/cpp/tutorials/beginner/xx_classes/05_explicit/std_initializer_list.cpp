// required even if the name is not explicitly used
#include <initializer_list>

auto f()
{
	auto list = {1, 2, 3}; // auto = std::initializer_list<int>
	return list; // return {1, 2, 3}; would require to specify function return type
}
