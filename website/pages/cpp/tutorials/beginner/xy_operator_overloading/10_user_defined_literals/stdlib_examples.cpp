#include <iostream>
#include <complex>
#include <chrono>
#include <string_view>

int main()
{
	{ // C++14
		using namespace std::complex_literals;
		auto c = 1.0f + 1.0if; // float(1.0) + std::complex<float>(0.0, 1.0)
		std::cout << "abs" << c << " = " << std::abs(c) << '\n';
	}

	{ // C++14
		using namespace std::chrono_literals;
		auto lesson = 45min;   // std::chrono::minutes, uses integers
		auto halfmin = 0.5min; // std::chrono::minutes, uses floating-point
		std::cout << "one lesson is " << lesson.count() << " minutes\n"
		          << "half a minute is " << halfmin.count() << " minutes\n";
	}

	{ // C++17
		using namespace std::string_view_literals;
		std::string_view s1 = "abc\0\0def"; // ctor that takes (const char*) - terminates on first null character
		std::string_view s2 = "abc\0\0def"sv; // literal that takes (const char*, std::size_t)
		std::cout << "s1: " << s1.size() << " \"" << s1 << "\"\n";
		std::cout << "s2: " << s2.size() << " \"" << s2 << "\"\n";
	}

	// C++20 (uncomment to enable)
	/* {
		using namespace std::chrono_literals;
		auto date = 1970y/1/1; // overloaded operator/ for year type and integers
		const auto now = std::chrono::system_clock::now();
		const auto today = std::chrono::year_month_day(std::chrono::sys_days(now));
		int leap_years = 0;
		while (date.year() <= today.year())
		{
			if (date.year().is_leap())
				++leap_years;
			date += std::chrono::years(1);
		}
		std::cout << "There have been " << leap_years << " leap years since the beginning of UNIX time.\n";
	} */
}
