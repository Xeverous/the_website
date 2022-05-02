// power_state.hpp
#ifndef EXAMPLE_PROJECT_POWER_STATE
#define EXAMPLE_PROJECT_POWER_STATE

enum class power_state { off, sleep, on };

#endif

// to_string.hpp
#ifndef EXAMPLE_PROJECT_TO_STRING
#define EXAMPLE_PROJECT_TO_STRING
#include "power_state.hpp"
#include <string>

std::string to_string(power_state ps);

#endif

// to_string.cpp
#include "to_string.hpp"
// (#include <string> can be safely ommited here because function declaration
// needs to include it anyway so including the header is enough)

std::string to_string(power_state ps)
{
	switch (ps)
	{
		case power_state::off:
			return "off";
		case power_state::sleep:
			return "sleep";
		case power_state::on:
			return "on";
		// no default case because this switch handles all possible values
		// if there is no default and a new enumerator is added, compilers will issue a warning
	}
}

// main.cpp
#include "power_state.hpp"
#include "to_string.hpp"

#include <iostream>

int main()
{
	auto state = power_state::on;
	std::cout << "device power state: " << to_string(state) << "\n";
}
