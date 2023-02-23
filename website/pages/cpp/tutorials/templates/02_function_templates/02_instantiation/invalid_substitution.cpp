template <typename T>
T* f1(T* p) { return p; }

template <typename T>
T f2(T*) {}

template <typename T>
T& f3(T* p) { return *p; }

int main()
{
	void* p = nullptr;
	f1(p);    // ok: returns void*
	f2(p);    // ok: returns void
	// f3(p); // error: type void& is invalid and *p is invalid

	int x = 1;
	f1(&x); // ok: returns int*
	f3(&x); // ok: returns int&

	// will compile, but has undefined behavior
	// (no return statement in function returning int)
	// f2(&x);
}
