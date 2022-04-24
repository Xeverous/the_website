/**
 * @class base class interface representing an arbitrary timer
 */
class timer
{
public:
	/**
	 * @brief start the timer
	 * @param precision number of ticks per second
	 * @param delay delay of the start in the unit of precision
	 * @return true if timer started, false if already running
	 * @details precision may be limited to max_precision()
	 * @sa max_precision
	 */
	virtual bool start(long precision, long delay) = 0;
	bool start(long precision) { return start(precision, 0); }
	bool start() { return start(max_precision()); }

	/**
	 * @brief stop the timer
	 * @return amount of passed time,
	 * empty optional if the timer wasn't running
	 */
	virtual std::optional<long> stop() = 0;

	/**
	 * @brief check whether the timer is running
	 * @return true if running, false otherwise
	 */
	virtual bool is_running() const = 0;

	/**
	 * @brief get maximum precision supported by the timer
	 * @return maximum precision supported
	 */
	virtual long max_precision() const = 0;
};
