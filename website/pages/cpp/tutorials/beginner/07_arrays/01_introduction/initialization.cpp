constexpr int n = 5;
int arr1[n]; // uninitialized
int arr2[n] = {}; // each element is zero-initialized
int arr3[n] = {1, 2}; // first 2 elements initialized explicitly, rest are zero-initialized
int arr4[n] = {1, 2, 3, 4, 5, 6}; // ill-formed: too many initializers

// array size can be inferred if it contains a non-empty initializer:
int arr[] = {1, 2, 3}; // ok: arr has size 3
