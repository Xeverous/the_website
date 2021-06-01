// valid C, UB in C++
union {
	int n;
	char bytes[4];
} packet;

packet.n = 1;
if (packet.bytes[0] == 1) // accessing other member
	// ...
