class player
{
private:
	int id;
	// lots of other fields... (potentially expensive to construct)

public:
	// [...]

	// reminder: friend functions defined inside classes are not members
	friend bool operator==(const player& lhs, const player& rhs)
	{
		return lhs.id == rhs.id;
	}
};

bool operator!=(const player& lhs, const player& rhs)
{
	return !(lhs == rhs);
}
