const char* path = "/bin/sh";
int legacy_interface(char* path); // documentation: does not modify path

int err = legacy_interface(const_cast<char*>(path)); // ok if path is not modified
