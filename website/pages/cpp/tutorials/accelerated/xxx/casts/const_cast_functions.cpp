struct test
{
	int m = 0;

	void f(int v) const
	{
		// this->m = v;                 // ill-formed: this has type const test*
		const_cast<test*>(this)->m = v; // ok if *this is not a const object
	}
};

test t;
t.f(1); // ok

const test ct;
ct.f(1); // invokes undefined behavior

void (test::* pmf)(int) const = &test::f;
// ill-formed: can not cast member function constness
// const_cast<void(test::*)(int)>(pmf);
