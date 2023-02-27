const char str1[] = "abc"; // array initialization (size is 4 due to null-terminating byte)
const char str2[] = { 'a', 'b', 'c', '\0' }; // equivalent to line above
const char* str3 = "abc"; // implicit convertion from const char[4] to const char*
