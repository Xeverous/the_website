#ifdef __linux__
	#include <unistd.h>
#elif defined(_WIN32)
	#include <windows.h>
#else
	#error unrecognized or unsupported platform
#endif

#include <string>

#ifdef _WIN32
std::string utf16_to_utf8(const wchar_t* wstr, int len)
{
	if (len == 0)
		return {};

	const int size = WideCharToMultiByte(CP_UTF8, 0, wstr, len, nullptr, 0, nullptr, nullptr);
	std::string result(size, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wstr, len, &result.front(), size, nullptr, nullptr);
	return result;
}
#endif

std::string get_path_to_executable()
{
#ifdef _WIN32
	wchar_t buf[MAX_PATH];
	return utf16_to_utf8(buf, GetModuleFileNameW(nullptr, buf, MAX_PATH));
#else
	char result[PATH_MAX];
	const ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	return std::string(result, (count > 0) ? count : 0);
#endif
}
