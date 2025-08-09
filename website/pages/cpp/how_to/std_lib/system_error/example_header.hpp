#include <system_error>

namespace lib {

enum class http_error
{
	no_error = 0,

	ok = 200,
	// ...
	bad_request = 400,
	forbidden = 403,
	not_found = 404,
	method_not_allowed = 405,
	// https://en.wikipedia.org/wiki/Hyper_Text_Coffee_Pot_Control_Protocol
	im_a_teapot = 418,
	// ...
};

const std::error_category& http_category() noexcept;

// this function can be picked by ADL
std::error_code make_error_code(http_error e) noexcept
{ return std::error_code(static_cast<int>(e), http_category()); }

} // namespace lib

namespace std {

// this enables std::error_code constructor overload for enums
template <>
struct is_error_code_enum<lib::http_error> : std::true_type {};

}
