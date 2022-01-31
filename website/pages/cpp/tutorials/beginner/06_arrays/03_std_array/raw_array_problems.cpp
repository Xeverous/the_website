int arr1[5] = {1, 2, 3, 4, 5};
int arr2[5] = {1, 2, 3, 4, 5};
int arr3[5] = arr2; // error: arrays can not be assigned to or initialized with other arrays

// workaround
struct sarr { int arr[5] };
sarr s1 = {1, 2, 3, 4, 5};
sarr s2 = s1; // ok

// this will compile, but behaves differently than expected
// it will compare memory adresses of arrays, not their contents
bool b = arr1 == arr2;
