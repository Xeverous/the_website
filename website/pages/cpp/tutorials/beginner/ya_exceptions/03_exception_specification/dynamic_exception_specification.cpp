// may throw std::runtime_error, std::bad_alloc or something derived from these
void f1() throw(std::runtime_error, std::bad_alloc);

// never throws any exceptions
void f2() throw();

// equivalent to the above, the preferred way since C++11
void f3() noexcept;
