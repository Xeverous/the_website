#include <fcntl.h>

// open a file - returns positive integer (fd) or -1 in case of error
int open(const char* path, int flags, mode_t mode);

// create a file - returns positive integer (fd) or -1 in case of error
// (yes, this function is named "creat", not "create")
int creat(const char* path, mode_t mode);

#include <sys/socket.h>

// open a socket - returns positive integer (fd) or -1 in case of error
int socket(int domain, int type, int protocol);
