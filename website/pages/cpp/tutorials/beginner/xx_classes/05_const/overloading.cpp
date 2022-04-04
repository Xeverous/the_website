class button
{
public:
	      std::string& text()       { return m_text; }
	const std::string& text() const { return m_text; }

	// [...] other methods

private:
	std::string m_text;
	// [...] other fields
};

// example use
// if the object is const-qualified, const-qualified overload is called
// the non-const overload returns non-const reference to the string
button btn1(/* ... */);
btn1.text() = "Exit";

const button btn2(/* ... */);
btn2.text() = "Exit"; // error: std::string::operator= is not const-qualified
