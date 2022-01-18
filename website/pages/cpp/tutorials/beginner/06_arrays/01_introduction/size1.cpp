int arr[] = {1, 2, 3};
// size = number of bytes that array occupies / number of bytes per element
constexpr int sz = sizeof(arr) / sizeof(arr[0]);
