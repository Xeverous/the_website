#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cerrno>

int file_size(const char* path, off_t& size)
{
	struct stat statbuf; // "struct" to use the type
	if (stat(path, &statbuf) != 0) // use the function
		return errno;

	size = statbuf.st_size;
	return 0;
}
