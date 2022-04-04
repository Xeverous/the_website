class cow_string
{
public:
	// always cheap to use this overload
	char operator[](int index) const
	{
		// directly return character
		return buffer->data[index];
	}

	// potentially expensive overload
	char& operator[](int index)
	{
		// if multiple string objects refer to the data...
		if (buffer->use_count > 1)
		{
			// ...make a copy of the data to support independent changes
			// (other string objects should remain unaffected)
			--buffer->use_count;
			buffer = allocate_buffer(size());
		}

		// now it's sure that returned non-const reference
		// is to a string that has exactly 1 use
		return buffer->data[index];
	}

private:
	shared_buffer* buffer;
};
