std::sort(entries.begin(), entries.end());
assert(!has_duplicates(entries));

bool has_duplicates(const std::vector<config_entry>& v)
{
	assert(std::is_sorted(v.begin(), v.end()));
	// after sorting, duplicate elements would be next to each other
	return std::adjacent_find(v.begin(), v.end()) != v.end();
}
