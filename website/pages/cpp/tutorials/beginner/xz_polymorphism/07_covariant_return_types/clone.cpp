class base
{
public:
	virtual base* clone() const
	{
		return new base(*this);
	}
};

class derived: public base
{
public:
	base* clone() const override
	{
		return new derived(*this);
	}
};

class more_derived: public derived
{
public:
	base* clone() const override
	{
		return new more_derived(*this);
	}
};
