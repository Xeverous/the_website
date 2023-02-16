#include <utility>
#include <cassert>
#include <algorithm>

class copyable
{
public:
	copyable() = default;

	copyable(const copyable& other)
	: m_size(other.m_size)
	{
		if (m_size > 0) {
			m_data = new double[m_size];
			copy_from(other.m_data, other.m_size);
		}
	}

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

	~copyable()
	{
		clear();
	}

	// (no move assignment because the overload above is optimal for both)

	friend void swap(copyable& lhs, copyable& rhs) noexcept
	{
		std::swap(lhs.m_data, rhs.m_data);
		std::swap(lhs.m_size, rhs.m_size);
	}

	void clear() noexcept
	{
		delete m_data;
		m_size = 0;
	}

private:
	void copy_from(const double* data, int size)
	{
		assert(m_size >= size);
		std::copy(data, data + size, m_data);
	}

	double* m_data = nullptr;
	int m_size = 0;
};

class moveable
{
	moveable() = default;

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
		m_size = 0;
	}

private:
	double* m_data = nullptr;
	int m_size = 0;
};
