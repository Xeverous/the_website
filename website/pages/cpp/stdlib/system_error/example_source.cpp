#include <lib.hpp>
#include <cerrno>

namespace lib {

namespace {

int map_error_code(int http_code) noexcept
{
	switch (http_code)
	{
		case 0: return 0;
		case 200: return 0;
		// ...
		case 403: return ACCES;
		case 404: return ENOENT;
		case 405: return ENOTSUP;
		// ...
		default: return EINVAL; // there is no better generic POSIX error
	}
}

class http_category_impl : public std::error_category
{
	const char* name() const noexcept override { return "HTTP"; }

	// the goal of this function is to translate errors for specific category to a generic one
	std::error_condition default_error_condition(int code) const noexcept override
	{
		return std::error_condition(map_error_code(code), std::generic_category());
	}

	std::string message(int condition) const override
	{
		switch (condition)
		{
			case 0: return "no error";
			case 200: return "ok";
			// ...
			case 403: return "forbidden";
			case 404: return "not found";
			case 405: return "method not allowed";
			case 418: return "I'm a teapot";
			// ...
			default: return "unknown error";
		}
	}
};
const http_category_impl http_category_instance;

}

const std::error_category& http_category() noexcept { return http_category_instance; }

}
