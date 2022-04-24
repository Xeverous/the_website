class base
{
public:
	virtual std::unique_ptr<base> clone() const
	{
		return std::make_unique<base>(*this);
	}
};

class derived: public base
{
public:
	std::unique_ptr<base> clone() const override
	{
		return std::make_unique<derived>(*this);
	}
};

class more_derived: public derived
{
public:
	std::unique_ptr<base> clone() const override
	{
		return std::make_unique<more_derived>(*this);
	}
};
