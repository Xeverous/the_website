#include <iostream>

int main()
{
	int x = 10;
	int y = 100;

	// Create and initialize a reference to x.
	// Reference variables do not create any new objects.
	int& ref = x; // A

	// All operations on the references work
	// as if they were perfomed on the bound object.
	++ref;
	std::cout << "x: " << x << "\n";
	std::cout << "x reference: " << ref << "\n";

	// The opposite direction is also true. All changes
	// to the variable are also visible through the reference.
	// Both refer to the same object in memory.
	++x;
	std::cout << "x: " << x << "\n";
	std::cout << "x reference: " << ref << "\n";

	// References can not be rebound. Once the refernece has been
	// initialized, all operations will be performed on the bound
	// object. This does not rebind the reference - it will always
	// refer to x. This statement is equivalent to x = y;
	ref = y; // B
	std::cout << "x: " << x << "\n";
	std::cout << "x reference: " << ref << "\n";
}
