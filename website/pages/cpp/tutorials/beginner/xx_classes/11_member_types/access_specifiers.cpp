class outer
{
public:
	class inner
	{
		void f(outer& o)
		{
			o.f(); // ok: inner is a member of outer so it can refer to non-public outer members
		}
	};

private:
	void f() {}
};
