namespace std {

class type_info
{
public:
	// you can not create objects of this (and derived) types
	// the only way is to use the typeid keyword
	type_info() = delete;

	// it is unspecified if this is actually called at the end of the program
	virtual ~type_info();

	type_info& operator=(const type_info&) = delete;
	type_info& operator=(type_info&&) = delete;

	// C++11: additionally noexcept
	// C++23: additionally constexpr
	bool operator==(const type_info& rhs) const;
	bool operator!=(const type_info& rhs) const;

	// C++11: all of these are also noexcept
	size_t hash_code() const;
	const char* name() const;
	bool before(const type_info& rhs) const;
};

// helper class to use it as a key in containers
// available since C++11
class type_index
{
public:
	type_index(const type_info& info) noexcept
	: info(&info) {}

	size_t hash_code() const noexcept { return info->hash_code(); }
	const char* name() const noexcept { return info->name(); }

	bool operator==(const type_index& rhs) const noexcept;
	bool operator!=(const type_index& rhs) const noexcept;
	bool operator< (const type_index& rhs) const noexcept;
	bool operator<=(const type_index& rhs) const noexcept;
	bool operator> (const type_index& rhs) const noexcept;
	bool operator>=(const type_index& rhs) const noexcept;
	// C++20
	strong_ordering operator<=>(const type_index& rhs) const noexcept;

private:
	type_info* info;
};

template <>
struct hash<type_index>
{
	size_t operator()(type_index index) const noexcept
	{
		return index.hash_code();
	}
};

}
