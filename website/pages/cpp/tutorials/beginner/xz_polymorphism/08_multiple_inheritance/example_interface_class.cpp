class logger
{
public:
	enum class severity { info, warning, error };

	virtual void message(severity s, const std::string& text) = 0;

	void info(const std::string& text) { message(severity::info, text); }
	void warning(const std::string& text) { message(severity::warning, text); }
	void error(const std::string& text) { message(severity::error, text); }
};
