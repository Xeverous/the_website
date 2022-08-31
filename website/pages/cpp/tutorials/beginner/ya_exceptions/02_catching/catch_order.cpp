#include <iostream>
#include <exception>

class a_exception : public std::exception {};
class b_exception : public a_exception {};
class c_exception : public b_exception {};
class d_exception : public c_exception {};

void func()
{
	// throw what you like here
}

int main()
{
	std::cout << "program start\n";

	try {
		std::cout << "before func()\n";
		func();
		std::cout << "after func()\n"; // if func() throws this is never executed
	}
	catch (const d_exception& e) {
		std::cout << "caught d exception\n";
	}
	catch (const c_exception& e) {
		std::cout << "caught c exception\n";
	}
	catch (const b_exception& e) {
		std::cout << "caught b exception\n";
	}
	catch (const a_exception& e) {
		std::cout << "caught a exception\n";
	}
	catch (const std::exception& e) {
		std::cout << "caught standard exception\n";
	}
	catch (...) {
		std::cout << "caught unknown exception\n";
	}

	std::cout << "program end\n";
}
