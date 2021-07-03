int x = 0;
int y = ++x + x++; // undefined behavior

x = ++x + 2;       // undefined behavior until C++11
x = x++ + 2;       // undefined behavior until C++17

std::cout << y << y++; // undefined behavior until C++17
func(++y, ++y);        // undefined behavior until C++17, unspecified after C++17

int z = --x + --y; // fine, x and y are 2 different objects
