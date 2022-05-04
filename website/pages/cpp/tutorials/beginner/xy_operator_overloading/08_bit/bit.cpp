perms& operator&=(perms& lhs, perms rhs)
{
	return lhs = static_cast<perms>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs));
}

perms& operator|=(perms& lhs, perms rhs)
{
	return lhs = static_cast<perms>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
}

perms& operator^=(perms& lhs, perms rhs)
{
	return lhs = static_cast<perms>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs));
}

perms operator&(perms lhs, perms rhs) { return lhs &= rhs; }
perms operator|(perms lhs, perms rhs) { return lhs |= rhs; }
perms operator^(perms lhs, perms rhs) { return lhs ^= rhs; }

perms operator~(perms rhs)
{
	// note that this will also flip bits which do not represent any option
	return static_cast<perms>(~static_cast<unsigned>(rhs));
}
