#include <iostream>

class user
{
public:
	user(/* params... */)
	: id(++id_counter) {}

	int get_id() const { return id; }

	// other member functions...

private:
	int id;
	// other fields (e.g. name, password, ...)

	static int id_counter;
};

// even private static members can be initialized this way
int user::id_counter = 0;

int main()
{
	user u1; // gets id == 1
	user u2; // gets id == 2

	{
		user u3; // gets id == 3
	} // u3 dies here; id == 3 will not be reused

	user u4; // gets id == 4
	std::cout << u4.get_id() << "\n";
}
