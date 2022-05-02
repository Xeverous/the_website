// before update
namespace lib {

	inline namespace v1 {
		void func();
	}

}

// after update
namespace lib {

	namespace v1 {
		void func();
	}

	inline namespace v2 {
		void func();
	}

}

void user_function()
{
	lib::v1::func(); // always first version

	// before update: v1::func
	// after update: v2::func
	lib::func();
}
