template <typename>
class function; // no primary definition

template <typename R, typename... Args>
class function<R(Args...)> // specialization only for function types
{
	using result_type = R;

	~function();

	function();               // empty state
	function(std::nullptr_t); // empty state

	function(const function& other); // copy
	function(function&& other);      // move, noexcept in C++20

	template <typename F>
	function(F&& f); // store f and allow to call it

	function& operator=(const function& other);
	function& operator=(function&& other); // interestingly not noexcept
	function& operator=(std::nullptr_t) noexcept; // reset to empty state

	// assign a new callable target
	template <typename F>
	function& operator=(F&& f);
	template <typename F>
	function& operator=(std::reference_wrapper<F> f) noexcept;

	void swap(function& other) noexcept;

	// return whether a target has been assigned
	// allows code like if (function_object) function_object();
	explicit operator bool() const noexcept;

	// invoke the target
	// throws std::bad_function_call if there is no target
	R operator()(Args... args) const;

	// returns typeid(T) if there is a target inside of type T
	// returns typeid(void) if there is no target
	const std::type_info& target_type() const noexcept;

	// obtain a pointer to the target, if there is a target of type T
	// otherwise return a null pointer
	template <typename T>
	T* target() noexcept;
	template <typename T>
	const T* target() const noexcept;
};

// compare function object with nullptr - test whether function is empty
template <typename R, typename... Args>
bool operator==(const std::function<R(Args...)>& f, std::nullptr_t) noexcept;
template <typename R, typename... Args>
bool operator==(std::nullptr_t, const std::function<R(Args...)>& f) noexcept;
template <typename R, typename... Args>
bool operator!=(const std::function<R(Args...)>& f, std::nullptr_t) noexcept;
template <typename R, typename... Args>
bool operator!=(std::nullptr_t, const std::function<R(Args...)>& f) noexcept;
