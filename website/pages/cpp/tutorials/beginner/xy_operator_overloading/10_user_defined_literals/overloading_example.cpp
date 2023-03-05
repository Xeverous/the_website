class celsius { /* ... */ };

constexpr celsius operator""_C(long double x)
{
	return celsius(x);
}

// example use
constexpr auto human_body_temperature = 36.6_C; // auto deduced to celsius
