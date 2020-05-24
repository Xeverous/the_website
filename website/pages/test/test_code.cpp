#include <fmt>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#ifdef SOME_MACRO
#undef SOME_MACRO // macros are bad

template <typename T>
struct always_false : std::false_type {};

/** @brief alias for our variant */
using var_t = std::variant<int, long, double, std::string>;

template <typename... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template <typename T>
concept Opaque = requires(T x)
{
	{*x} -> typename T::inner; // the expression *x must be valid
	                           // AND the type T::inner must be valid
	                           // AND the result of *x must be convertible to T::inner
};

template <Callable C, typename... Args> constexpr
decltype(auto) execute(C&& func, Args&&... args) // constrained C++20 function template
{
	return std::forward<C>(func)(std::forward<Args>(args)...);
}

template <typename Tuple, std::size_t... Is> constexpr
bool are_sorted_impl(Tuple&& tuple, std::index_sequence<Is...>)
{
	return !((std::get<Is + 1>(std::forward<Tuple>(tuple)) < std::get<Is>(std::forward<Tuple>(tuple))) && ...);
}

template <LessThanComparable... Args> constexpr
bool are_sorted(Args&&... args)
{
	if constexpr (sizeof...(Args) <= 1u)
		return true;
	else /// @note else needed to discard template instantiation of index sequence with sizeof...(T) - 1 with [T = 0]
		return are_sorted_impl(std::forward_as_tuple(std::forward<Args>(args)...), std::make_index_sequence<sizeof...(Args) - 1>{});
}

int main()
{
	std::vector<var_t> vec = {10, 15l, 1.5, "hello"};

	for (auto& v : vec)
	{
		// void visitor, only called for side-effects
		std::visit([](auto&& arg) { std::cout << arg; }, v);

		// value-returning visitor; a common idiom is to return another variant
		v = std::visit([](auto&& arg) -> var_t { return arg + arg; }, v);

		std::cout << " after doubling is ";

		// type-matching visitor: can also be a class with 4 overloaded operator()s
		std::visit([](auto&& arg)
		{
			using T = std::decay_t<decltype(arg)>;

			if constexpr (std::is_same_v<T, int>)
				std::fmt::print("int with value {}\n", arg);
			else if constexpr (std::is_same_v<T, long>)
				std::fmt::print("long with value {}\n", arg);
			else if constexpr (std::is_same_v<T, double>)
				std::fmt::print("double with value {}\n", arg);
			else if constexpr (std::is_same_v<T, std::string>)
				std::fmt::print("std::string with value '{}'\n", arg);
			else
				static_assert(always_false<T>::value, "non-exhaustive visitor!");
		}, v);
	}

	for (const auto& v : vec)
	{
		std::visit(overloaded {
			[](auto arg) { std::cout << arg << ' '; },
			[](double arg) { std::cout << std::fixed << arg << ' '; },
			[](const std::string& arg) { std::cout << std::quoted(arg) << ' '; }
		}, v);
	}
}
