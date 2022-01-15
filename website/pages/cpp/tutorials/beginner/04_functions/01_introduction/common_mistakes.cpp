#include <iostream>

void greet()
{
	std::cout << "hello, world";
}

int get_std_year()
{
	// macro is a number in the form YYYYMM
	return __cplusplus / 100;
}

int main()
{
	// feeding std::cout with "data of type void"
	// the function should either be called directly or return the string
	// this will not compile and likely print many overloads of operator<<
	// and explain for each overload why it does not match (pretty long list)
	std::cout << greet();

	// attempting to call a function with no actual call - missing ()
	// this expression is valid (it will just evaluate function address)
	// may print a warning that this statement has no effect
	greet;

	// as above, now just printing address of the function
	// this will compile and print some non-zero value
	std::cout << get_std_year;
}
