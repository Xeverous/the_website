struct S { double x; };
const S* ptr;

decltype(ptr->x) y;       // type of y is double (declared type)
decltype((ptr->x)) z = y; // type of z is const double& (lvalue expression)
