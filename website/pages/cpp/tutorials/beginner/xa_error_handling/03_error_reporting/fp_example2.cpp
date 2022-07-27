boost::optional<std::size_t> get_user_id(); // empty result if not logged
user_stats_t get_user_stats(std::size_t user_id);
std::chrono::seconds compute_active_time(const user_stats_t& stats);

auto time_active = get_user_id() // boost::optional<std::size_t>
	.map(get_user_stats) // boost::optional<std::size_t> => boost::optional<user_stats_t>
	.map(compute_active_time) // boost::optional<user_stats_t> => boost::optional<std::chrono::seconds>
	.value_or(std::chrono::seconds(0)); // boost::optional<std::chrono::seconds> => std::chrono::seconds
	// auto = std::chrono::seconds
