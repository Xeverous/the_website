extern int a1[];
int (&r1)[] = a1;  // ok (C++ only code)
int (*p1)[] = &a1; // ok in C, ok in C++
int (*q)[2] = &a1; // ok in C, error in C++

int a2[] = {1, 2, 3};
int (&r2)[] = a2;  // error (C++ only code)
int (*p2)[] = &a2; // ok in C, error in C++
