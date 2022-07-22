#define ASSERT_MSG(condition, message) assert(((void)(message), condition))
#define ASSERT_MSG(condition, message) assert((condition) && message)
