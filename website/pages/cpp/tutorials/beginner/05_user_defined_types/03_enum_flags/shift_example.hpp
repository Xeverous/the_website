// hypothetical implementation of std::filesystem::copy_options
// https://en.cppreference.com/w/cpp/filesystem/copy_options
enum class copy_options : unsigned short
{
	none = 0,

	skip_existing = 1 << 0,
	overwrite_existing = 1 << 1,
	update_existing = 1 << 2,

	recursive = 1 << 3,

	copy_symlinks = 1 << 4,
	skip_symlinks = 1 << 5,

	directories_only = 1 << 6,
	create_symlinks = 1 << 7,
	create_hard_links = 1 << 8
};
