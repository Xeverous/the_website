void f(int arr[3]); // array argument of size 3
void f(int arr[]);  // array argument of unspecified size

// both above are equivalent to this
void f(int* arr); // pointer argument

// this is something different (VLA argument) and applies only to C
// since C++ (officially) has no VLAs, this is a syntax error
void f(int arr[*]);
