// error: can not bind rvalue to non-const lvalue reference
int& x = 1;

// ok, lifetime of 1 is extended to the lifetime of y
// (normally object 1 would be destroyed at ;)
const int& y = 1;

// error: can not bind const object to non-const reference
int& z = y;
