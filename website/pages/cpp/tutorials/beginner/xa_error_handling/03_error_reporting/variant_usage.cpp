std::variant<int, std::errc> result = safe_divide(x, y);
if (std::holds_alternative<int>(result))
	use_result(std::get<int>(result));
else
	std::cout << std::error_code(std::get<std::errc>(result)).message() << "\n";
