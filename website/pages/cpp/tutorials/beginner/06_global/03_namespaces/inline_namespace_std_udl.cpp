// synopsis from standard library implementation
namespace std {

	inline namespace literals {
		// note: there are more literal overloads than listed here

		inline namespace string_literals {
			constexpr string operator""s(const char* str, size_t len); // constexpr since C++20
		}

		inline namespace chrono_literals {
			constexpr chrono::seconds operator""s(unsigned long long secs);
		}
	}

	namespace chrono {
		using namespace literals::chrono_literals;
	}

}

// example uses
{
	using namespace std; // makes both suffixes visible
	auto str = "abc"s; // auto = std::string
	auto min = 60s;    // auto = std::chrono::seconds
}

{
	using namespace std::literals; // makes both suffixes visible
	auto str = "abc"s;
	auto min = 60s;
}

{
	using std::operator""s; // makes both suffixes visible
	auto str = "abc"s;
	auto min = 60s;
}

{
	using namespace std::string_literals; // string literal suffixes only
	auto str = "abc"s;
}

{
	using namespace std::chrono_literals; // chrono literal suffixes only
	auto min = 60s;
}

{
	using namespace std::chrono; // all std::chrono names, including suffixes
	auto min = 60s;
	auto sec = seconds(1); // auto = std::chrono::seconds
}
