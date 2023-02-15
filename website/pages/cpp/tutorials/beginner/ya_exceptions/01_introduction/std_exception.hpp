class string;

namespace std {

class exception
{
public:
	exception() noexcept;
	exception(const exception& other) noexcept;
	exception& operator=(const exception& other) noexcept;
	virtual ~exception() noexcept;

	// the string is implementation-defined
	// both GCC and Clang return "std::exception"
	virtual const char* what() const noexcept;
};

class runtime_error : public exception
{
	// note: there is no default ctor
	runtime_error(const string& what_arg);
	runtime_error(const char* what_arg);

	runtime_error(const runtime_error& other) noexcept;
	runtime_error& operator=(const runtime_error& other) noexcept;

	// returns the string that was passed to the ctor
	// implementations are allowed to do so through other means than overriding
	const char* what() const noexcept override;
};

}
