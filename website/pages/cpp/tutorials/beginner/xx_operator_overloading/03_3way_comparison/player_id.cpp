class player
{
private:
	int id;
	// lots of other fields... (potentially expensive to construct)

public:
	// [...]

	bool operator==(const player& rhs) const
	{
		return id == rhs.id;
	}

	bool operator==(int other_id) const
	{
		return id == other_id;
	}
};
