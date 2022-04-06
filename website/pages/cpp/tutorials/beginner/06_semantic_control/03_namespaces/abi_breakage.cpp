namespace gis {

	struct geo_zone {
		// [...]
		// additional and/or reordered members in newer version
	};

}

void user_func()
{
	// compiled user code with old version (function-local object):
	// allocates sizeof(gis::geo_zone) bytes on the stack with alignof(gis::geo_zone) alignment
	// compiled library code with new version (library function):
	// writes sizeof(gis::geo_zone) bytes, *this size may differ from size in user code*
	// result: possible stack memory corruption, overwrite of other data on the stack
	gis::geo_zone gz = gis::some_func();
	// compiled user code with old version (member of a type):
	// passes to the function memory address of gz, adjusted by offsetof(gis::geo_zone, time_zone)
	// compiled library code with new version (library function):
	// expects the struct member at a different offset, may break under some optimizations
	gis::other_func(gz.time_zone);
}
