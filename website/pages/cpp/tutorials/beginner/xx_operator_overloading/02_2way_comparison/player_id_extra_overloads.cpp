// inside class definition
friend bool operator==(const player& lhs, int id)
{
	return lhs.id == id;
}

// outside class definition
bool operator==(int id, const player& rhs)
{
	return rhs == id;
}

bool operator!=(const player& lhs, int id)
{
	return !(lhs == id);
}

bool operator!=(int id, const player& rhs)
{
	return !(id == rhs);
}
