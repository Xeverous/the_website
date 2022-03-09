namespace std {

enum class errc { /* constants defined as aliases of POSIX error numbers */ };

template <typename T>
struct is_error_code_enum : false_type {};
template <typename T>
struct is_error_condition_enum : false_type {};
// other specializations (for std::io_errc and std::future_errc) defined in other headers
template <>
struct is_error_condition_enum<errc> : true_type {};

class error_category
{
public:
	virtual ~error_category();
	error_category& operator=(const error_category&) = delete;

	virtual const char* name() const noexcept = 0;

	virtual error_condition default_error_condition(int code) const noexcept
	{ return error_condition(code, *this); }

	virtual bool equivalent(int code, const error_condition& condition) const noexcept
	{ return default_error_condition(code) == condition; }

	virtual bool equivalent(const error_code& code, int condition) const noexcept
	{ return *this == code.category() && code.value() == condition; }

	virtual string message(int condition) const = 0;

	// in C++11 operators: ==, !=, <
	// in C++20 operators: ==, <=>, rest synthesised
	strong_ordering operator<=>(const error_category& rhs) const noexcept;
};

const error_category& generic_category() noexcept; // POSIX error codes
const error_category& system_category() noexcept; // platform-specific error codes

class error_code
{
public:
	error_code() noexcept : error_code(0, system_category()) {}
	error_code(int ec, const error_category& ecat) noexcept : ec(ec), ecat(&ecat) {}
	template <
		typename ErrorCodeEnum,
		typename enable_if<is_error_code_enum<ErrorCodeEnum>::value>::type* = nullptr
	>
	error_code(ErrorCodeEnum e) noexcept;

	template <
		typename ErrorCodeEnum,
		typename enable_if<is_error_code_enum<ErrorCodeEnum>::value>::type* = nullptr
	>
	error_code& operator=(ErrorCodeEnum e) noexcept;

	void assign(int ec, const error_category& ecat) noexcept
	{
		this->ec = ec;
		this->ecat = &ecat;
	}

	void clear() noexcept { *this = error_code(); }

	int value() const noexcept { return ec; }
	const error_category& category() const noexcept { return *ecat; }

	error_condition default_error_condition() const noexcept
	{ return category().default_error_condition(value()); }

	string message() const { return category().message(value()); }

	explicit operator bool() const noexcept { return value() != 0; }

private:
	int ec;
	const error_category* ecat;
};

// in C++11 operators: ==, !=, <
// in C++20 operators: ==, <=>, rest synthesised
strong_ordering operator<=>(const error_code& lhs, const error_code& rhs) noexcept;

template <typename CharT, typename Traits>
basic_ostream<CharT, Traits>& operator<<(basic_ostream<CharT, Traits>& os, const error_code& ec)
{
	return os << ec.category().name() << ':' << ec.value();
}

class error_condition
{
	// [...] analogically same as error_code but:
	// - has no default_error_condition
	// - has no operator<<
};

error_code make_error_code(errc e) noexcept
{ return error_code(static_cast<int>(e), generic_category()); }
error_condition make_error_condition(errc e) noexcept
{ return error_condition(static_cast<int>(e), generic_category()); }

template <>
struct hash<error_code>
{
	size_t operator()(error_code ec) noexcept;
}

class system_error : public runtime_error
{
public:
	system_error(error_code ec, const string& what_arg);
	system_error(error_code ec, const char* what_arg);
	system_error(error_code ec);
	system_error(int ev, const error_category& ecat, const string& what_arg);
	system_error(int ev, const error_category& ecat, const char* what_arg);
	system_error(int ev, const error_category& ecat);

	const error_code& code() const noexcept;
	const char* what() const noexcept override;
};

} // namespace std
