// since C++11
// if the static member is const, it can be initialized in the class definition
struct foo
{
	static const int s = 1; // static const is implicitly inline
};

// since C++11
// if the static member is constexpr, it has to be initialized in the class definition
struct bar
{
	static constexpr int s = 1; // constexpr initialization implies inline
};

// since C++17
// static members can be marked inline and initialized in the class definition
struct baz
{
	inline static int s = 1;
};
