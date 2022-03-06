int x = 1;
const int& rx = x;
const_cast<int&>(rx) = 2; // ok: object is not actually const

const int y = 1;
const int& ry = y;
const_cast<int&>(ry) = 2; // undefined behavior
