int start_process(const char* cmd, bool capture_std_err = true, bool capture_std_out = true, bool detach = false);

// ...

int pid = start_process(cmd, true, false, true); // hard to read without remembering precise order of parameters
