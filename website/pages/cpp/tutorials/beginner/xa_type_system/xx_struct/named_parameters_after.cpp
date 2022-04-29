struct process_options
{
	bool capture_std_err = true;
	bool capture_std_out = true;
	bool detach = false;
};

int start_process(const char* cmd, process_options options);

// ...

process_options options;
options.capture_std_err = true;
options.capture_std_out = false;
options.detach = true;
int pid = start_process(cmd, options);
