#include <iostream>

#define STRINGIZE_IMPL(x) #x
#define STRINGIZE(x) STRINGIZE_IMPL(x)

#define PRINT1(val) std::cout << #val " = " << val << "\n"
#define PRINT2(val) std::cout << STRINGIZE(val) " = " << val << "\n"

#define VALUE x + y

int main()
{
	int x = 1;
	int y = 2;
	PRINT1(VALUE); // immediately stringizes macro argument name
	PRINT2(VALUE); // stringizes after inner macro expansion
}
