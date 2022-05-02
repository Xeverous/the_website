// print to standard output
int printf(const char* format, ...);
// print to specified stream - printf(args...) is equivalent to fprintf(stdout, args...)
int fprintf(std::FILE* stream, const char* format, ...);
// print to a buffer
int sprintf(char* buffer, const char* format, ...);
// print to a buffer with specified maximum size
int snprintf(char* buffer, std::size_t buf_size, const char* format, ...);
