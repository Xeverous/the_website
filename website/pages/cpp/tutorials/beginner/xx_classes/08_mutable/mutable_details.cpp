struct test
{
	mutable       int* p1;       // ok
	mutable const int* p2;       // ok
	mutable       int* const p3; // error
	mutable const int* const p4; // error
	mutable int&       r;        // error
	mutable static int s;        // error
};
