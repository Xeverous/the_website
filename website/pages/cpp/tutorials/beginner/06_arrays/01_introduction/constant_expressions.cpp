constexpr int n1 = 10;
const int n2 = 10;
const int n3 = non_constexpr_function();

int arr1[n1]; // ok
int arr2[n2]; // also ok (n2 can be evaluated at compile time)
int arr3[n3]; // error: size not a constant expression

int n4 = 10;
const int n5 = n4; // const, but not compile-time
int arr5[n5]; // error: n5 is no a constant expression
