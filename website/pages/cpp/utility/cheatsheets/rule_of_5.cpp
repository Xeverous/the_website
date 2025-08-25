#include <utility>
#include <algorithm>

class copyable
{
public:
	copyable() = default;

	copyable(const double* data, int size)
	: m_size(size)
	{
		if (size > 0) {
			m_data = new double[size];
			std::copy(data, data + size, m_data);
		}
	}

	copyable(const copyable& other)
	: copyable(other.m_data, other.m_size)
	{}

	copyable(copyable&& other) noexcept
	{
		swap(*this, other);
	}

	// copy and swap idiom (4 special member functions + swap)
	copyable& operator=(copyable other) noexcept
	{
		swap(*this, other);
		return *this;
	}

	// (no move assignment because the overload above is optimal for both)

	~copyable()
	{
		clear();
	}

	friend void swap(copyable& lhs, copyable& rhs) noexcept
	{
		std::swap(lhs.m_data, rhs.m_data);
		std::swap(lhs.m_size, rhs.m_size);
	}

	void clear() noexcept
	{
		delete m_data;
		m_data = nullptr;
		m_size = 0;
	}

	double* data() { return m_data; }
	const double* data() const { return m_data; }
	int size() { return m_size; }

private:
	double* m_data = nullptr;
	int m_size = 0;
};

class moveable
{
	moveable() = default;

	moveable(const double* data, int size)
	: m_size(size)
	{
		if (size > 0) {
			m_data = new double[size];
			std::copy(data, data + size, m_data);
		}
	}

	moveable(const moveable& other) = delete;
	moveable(moveable&& other) noexcept
	{
		swap(*this, other);
	}

	moveable& operator=(const moveable& other) = delete;
	moveable& operator=(moveable&& other) noexcept
	{
		swap(*this, other);
		return *this;
	}

	~moveable()
	{
		clear();
	}

	friend void swap(moveable& lhs, moveable& rhs) noexcept
	{
		std::swap(lhs.m_data, rhs.m_data);
		std::swap(lhs.m_size, rhs.m_size);
	}

	void clear() noexcept
	{
		delete m_data;
		m_data = nullptr;
		m_size = 0;
	}

	double* data() { return m_data; }
	const double* data() const { return m_data; }
	int size() { return m_size; }

private:
	double* m_data = nullptr;
	int m_size = 0;
};
