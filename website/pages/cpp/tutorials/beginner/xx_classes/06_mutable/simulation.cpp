class simulation
{
public:
	bool set_amount(int value)
	{
		if (value < 1)
			return false;

		amount = value;
		return true;
	}

	bool set_time(double ms)
	{
		if (value < 0.0)
			return false;

		time_ms = ms;
		return true;
	}

	bool set_velocity(double value)
	{
		velocity = value;
		return true;
	}

	// more setters...

	simulation_result compute_result() const; // very expensive

private:
	int amount;
	double time_ms;
	double velocity;
	// more data members...
};
