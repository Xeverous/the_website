#include <stdexcept>
int may_throw();

int func()
{
	auto handler = [](const std::exception& /* e */) {
		/* do stuff with e */
		return 0;
	}

	try {
		return may_throw();
	}
	catch (const std::runtime_error& e) {
		return handler(e);
	}
	catch (const std::bad_function_call& e) {
		return handler(e);
	}
	catch (const std::bad_optional_access& e) {
		return handler(e);
	}

	// This function produces no control flow warnings!
	// Any code here is unreachable - func either:
	// - executes return from the try block
	// - returns from a handler
	// - exits via uncaught exception
}
