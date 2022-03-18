int arr[] = {1, 2, 3, 4, 5, 6};
// ok: sizeof(array) / sizeof(element)
const auto sz1 = sizeof(arr) / sizeof(arr[0]);

// this is what happens when array is passed to a function
const int* ptr = arr; // some type information is lost
// wrong: sizeof(pointer) / sizeof(element)
const auto sz2 = sizeof(ptr) / sizeof(ptr[0]);
