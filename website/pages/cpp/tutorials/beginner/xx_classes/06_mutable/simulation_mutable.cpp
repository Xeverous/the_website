class simulation
{
public:
	bool set_amount(int value)
	{
		if (value < 1)
			return false;

		if (value != amount)
		{
			amount = value;
			last_result = std::nullopt;
		}

		return true;
	}

	bool set_time(double ms)
	{
		if (value < 0.0)
			return false;

		if (ms != time_ms)
		{
			time_ms = ms;
			last_result = std::nullopt;
		}

		return true;
	}

	bool set_velocity(double value)
	{
		if (value != velocity)
		{
			velocity = value;
			last_result = std::nullopt;
		}

		return true;
	}

	// more setters...

	simulation_result get_result() const
	{
		if (!last_result)
			last_result = compute_result();

		return last_result.value();
	}

private:
	simulation_result compute_result() const;

	int amount;
	double velocity;
	double time_ms;
	// more data members...

	mutable std::optional<simulation_result> last_result;
};
