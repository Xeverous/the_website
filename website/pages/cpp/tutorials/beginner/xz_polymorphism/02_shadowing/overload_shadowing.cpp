// classes can be forward declared
// but the only thing allowed to do is forming pointers and references
// any actual work on the class (object creation, calling functions) requires definition
class image;

class text_button
{
public:
	void set_content(std::string /* text */) { /* ... */ }

// [...]
};

class image_text_button: public text_button
{
public:
	// expected: add another overload
	// actual: hides all base type overloads
	void set_content(const image& /* img */) { /* ... */ }
};

void func(const image& img)
{
	image_text_button btn;
	btn.set_content(img);      // ok
	btn.set_content("cancel"); // error: argument type mismatch
}
