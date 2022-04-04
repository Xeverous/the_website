#include <utility>

char get_first_char()
{
	cow_string str = returns_str_from_somewhere();

	if (str.empty())
		return '\0';

	// bad: potentially expensive call
	// return str[0];

	// good: std::as_const returns const reference
	// now a const-qualified overload of operator[] will be used
	return std::as_const(str)[0];
}
