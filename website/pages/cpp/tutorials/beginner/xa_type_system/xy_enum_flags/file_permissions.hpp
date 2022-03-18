namespace std::filesystem {

enum class perms
{
	none = 0,

	owner_read = 0400,
	owner_write = 0200,
	owner_exec = 0100,
	owner_all = owner_read | owner_write | owner_exec,

	group_read = 040,
	group_write = 020,
	group_exec = 010,
	group_all = group_read | group_write | group_exec,

	others_read = 04,
	others_write = 02,
	others_execute = 01,
	others_all = others_read | others_write | others_execute,

	all = owner_all | group_all | others_all,

	set_uid = 04000,
	set_gid = 02000,
	sticky_bit = 01000,

	mask = all | set_uid | set_gid | sticky_bit
};

perms operator&(perms lhs, perms rhs);
perms operator|(perms lhs, perms rhs);
perms operator^(perms lhs, perms rhs);

perms& operator&=(perms& lhs, perms rhs);
perms& operator|=(perms& lhs, perms rhs);
perms& operator^=(perms& lhs, perms rhs);

perms operator~(perms rhs);

}
