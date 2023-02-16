	moveable(moveable&& other) noexcept
	: m_data(std::exchange(other.m_data, nullptr))
	, m_size(std::exchange(other.m_size, 0))
	{}
