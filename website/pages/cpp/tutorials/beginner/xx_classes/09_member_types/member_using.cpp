class config
{
public:
	using container_type = std::unordered_map<std::string, boost::container::small_vector<long>>;

	void revert()
	{
		curr = prev;
	}

	void commit()
	{
		save_on_disk();
		prev = curr;
	}

	      container_type& current()       { return curr; }
	const container_type& current() const { return curr; }

private:
	save_on_disk();

	container_type curr;
	container_type prev;
};
