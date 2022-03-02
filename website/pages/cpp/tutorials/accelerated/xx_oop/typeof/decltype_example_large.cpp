auto x = 1;              // type of x is int - template type deduction
decltype(auto) d1 = x;   // type of d1 is int - decltype(x)
decltype(auto) d2 = (x); // type of d2 is int& - decltype((x))

// auto - perfect_forward will always return by value
// decltype(auto) - perfect_forward return type will be decltype(return_expr)
// (it will return T& if fun returns T& and T&& if fun returns T&&)
template <typename F, typename... Args>
decltype(auto) perfect_forward(F fun, Args&&... args)
{
	return fun(std::forward<Args>(args)...);
}
