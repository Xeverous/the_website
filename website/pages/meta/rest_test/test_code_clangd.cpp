#include <iostream>
#include <utility>

#define EMPTY
#define PRINT(x) \
	std::cout << #x " = " << (x) << "\n"

#ifndef EMPTY
#define BUG
#error Misconfigured build!
auto disabled_function()
{
	/// TODO fix compilation
	return non_existent_function(3.14f, "test");
}
#endif

// some comment
template <typename T>
struct test
{
	/**
	 * @brief reset an object of type T
	 * @param value the object
	 * @return void
	 */
	void reset(T& value) const noexcept(noexcept(T{}))
	{
		// TODO make a version with T()
		value = EMPTY T{};
	}

	template <typename U = T>
	decltype(auto) func(U&& object) const noexcept(noexcept(std::declval<U&&>().func()))
	{
		return std::forward<U>(object).func();
	}
};

[[nodiscard]] long long factorial(long long n)
{
	if (n < 2)
		return 1;
	else
		return n * factorial(n - 1);
}

#define X(g, ...)
auto global = /* not so multiline comment */ 123.456l;
# /// lone hash shouldn't be a problem

namespace anything { enum class something { one, two, three }; }

auto main() -> int
{
	test<decltype(global)>{}.reset(global);
	auto str_lit = R"test(raw\nstring\nliteral)test";
	PRINT(str_lit);
	const auto& fmt = L"pointer = %p, length = %zu, string = %s";
	std::cout << "sizeof(fmt) = " << sizeof(fmt) << "\n";
}
