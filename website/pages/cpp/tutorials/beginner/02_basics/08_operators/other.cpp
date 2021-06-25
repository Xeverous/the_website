#include <iostream>

int main()
{
	std::cout << "size of bool       : " << sizeof(bool)        << "\n";
	std::cout << "size of int        : " << sizeof(int)         << "\n";
	std::cout << "size of long       : " << sizeof(long)        << "\n";
	std::cout << "size of long long  : " << sizeof(long long)   << "\n";
	std::cout << "size of char       : " << sizeof(char)        << "\n";
	std::cout << "size of char16_t   : " << sizeof(char16_t)    << "\n";
	std::cout << "size of char32_t   : " << sizeof(char32_t)    << "\n";
	std::cout << "size of wchar_t    : " << sizeof(wchar_t)     << "\n";
	std::cout << "size of float      : " << sizeof(float)       << "\n";
	std::cout << "size of double     : " << sizeof(double)      << "\n";
	std::cout << "size of long double: " << sizeof(long double) << "\n";

	std::cout << "alignment of bool       : " << alignof(bool)        << "\n";
	std::cout << "alignment of int        : " << alignof(int)         << "\n";
	std::cout << "alignment of long       : " << alignof(long)        << "\n";
	std::cout << "alignment of long long  : " << alignof(long long)   << "\n";
	std::cout << "alignment of char       : " << alignof(char)        << "\n";
	std::cout << "alignment of char16_t   : " << alignof(char16_t)    << "\n";
	std::cout << "alignment of char32_t   : " << alignof(char32_t)    << "\n";
	std::cout << "alignment of wchar_t    : " << alignof(wchar_t)     << "\n";
	std::cout << "alignment of float      : " << alignof(float)       << "\n";
	std::cout << "alignment of double     : " << alignof(double)      << "\n";
	std::cout << "alignment of long double: " << alignof(long double) << "\n";

	// This syntax is also valid, but because many type names consist of
	// multiple keywords and functions always use (), it's heavily
	// recommended to always use (), just like with functions.
	// std::cout << "size of int: " << sizeof int << "\n";

	// These operators can also be used with objects, in which case
	// they will output the size/alignment of the type of the object.
	std::cout << "size of character output object: " << sizeof(std::cout) << "\n";
	std::cout << "alignment of character output object: " << alignof(std::cout) << "\n";
}
