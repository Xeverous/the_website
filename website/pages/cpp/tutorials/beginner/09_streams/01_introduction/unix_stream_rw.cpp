#include <unistd.h>

// copy up to count bytes from the stream identified by fd to the buffer
ssize_t read(int fd, void* buf, size_t count);

// copy up to count bytes from buffer to the stream identified by fd
ssize_t write(int fd, const void* buf, size_t count);
