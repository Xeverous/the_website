void run_simulation(double speed = 1.0);
std::optional<double> to_double(std::string_view sv);

// read config, convert string to double
// if convertion fails use value 1.0
run_simulation(to_double(config.speed).value_or(1.0));
