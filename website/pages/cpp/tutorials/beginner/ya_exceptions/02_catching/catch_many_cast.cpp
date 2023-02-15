#include <stdexcept>
#include <optional>
#include <functional>

int may_throw();

int func()
{
	try {
		return may_throw();
	}
	catch (const std::exception& e) {
		if (auto ptr = dynamic_cast<const std::runtime_error*>(&e); ptr != nullptr) {
			// handle runtime_error
			return 0;
		}
		else if (auto ptr = dynamic_cast<const std::bad_function_call*>(&e); ptr != nullptr) {
			// handle bad_function_call
			return 0;
		}
		else if (auto ptr = dynamic_cast<const std::bad_optional_access*>(&e); ptr != nullptr) {
			// handle bad_optional_access
			return 0;
		}
		else {
			throw; // rethrow exception
		}
	}

	// (unreachable code)
}
