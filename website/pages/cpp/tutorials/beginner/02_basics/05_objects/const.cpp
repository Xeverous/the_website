// const objects must be initialized
const int x; // error: constant not initialized

// const objects can not be assigned to
const int x = 10;
x = 5; // error: x is const

// const may be initialized from non-const:
int a = 10;
const int b = a; // ok
