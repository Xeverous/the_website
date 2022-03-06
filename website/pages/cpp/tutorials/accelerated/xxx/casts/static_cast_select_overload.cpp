template <typename F> constexpr
F& select_overload(F& f) noexcept { return f; }

invoke(select_overload<void(int, int)>(f), 1, 2); // ok
