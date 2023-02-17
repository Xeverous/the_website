class singleton
{
public:
	singleton& get_instance()
	{
		static singleton instance(/* args... */);
		return instance;
	}

	// remove every other possibility of object creation
	// copy/move ctor/operator= are explained in RAII chapter
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;
	singleton(singleton&&) = delete;
	singleton& operator=(singleton&&) = delete;

	// public functions that offer actual functionality...

private:
	singleton(/* ctor arguments... */);

	// state...
};
