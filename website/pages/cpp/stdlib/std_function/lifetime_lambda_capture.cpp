std::function<int()> f;

{
	int x = 42;
	f = [&](){ return x; };
}

f(); // undefined behavior: x is already dead
