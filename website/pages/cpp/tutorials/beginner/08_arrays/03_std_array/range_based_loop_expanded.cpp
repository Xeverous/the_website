{ // C++11 and C++14
	auto&& __range = range-expression;
	for (auto __begin = begin_expr, __end = end_expr; __begin != __end; ++__begin) {
		range-declaration = *__begin;
		loop-statement
	}
}
{ // C++17 and later (begin_expr and end_expr can be different types)
	init-statement // since C++20, if provided
	auto&& __range = range-expression;
	auto __begin = begin_expr;
	auto __end = end_expr;
	for (; __begin != __end; ++__begin) {
		range-declaration = *__begin;
		loop-statement
	}
}
