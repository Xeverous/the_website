// at the end of configuration loading
assert(!has_duplicates(entries));

// elsewhere - function definition
bool has_duplicates(std::vector<config_entry>& v)
{
	std::sort(v.begin(), v.end());
	// after sorting, duplicate elements would be next to each other
	return std::adjacent_find(v.begin(), v.end()) != v.end();
}
