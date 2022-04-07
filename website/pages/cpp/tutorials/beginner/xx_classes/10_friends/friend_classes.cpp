using int_t = int;
class quux {};
class bar {};

class foo
{
private: // friend declarations are not affected by access specifiers so it doesn't matter which keyword is here
	friend int_t; // ok: the type exists but is not a class - statement ignored
	friend fp_t;  // error: type fp_t does not exist
	friend quux;  // ok: quux can access private and protected members of foo
	friend class bar; // ok: bar can access private and protected members of foo
	friend class baz; // as above + also forward declares class baz

	friend class bzz {}; // error: friended class definition inside enclosing class not allowed
};
