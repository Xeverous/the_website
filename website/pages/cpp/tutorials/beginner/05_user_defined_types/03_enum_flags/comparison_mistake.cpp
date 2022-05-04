// wrong: this checks for equality of all bits
if (p == std::filesystem::perms::owner_read)
	// ...

// correct: check only for presence of specific bit
if (p & std::filesystem::perms::owner_read)
	// ...
