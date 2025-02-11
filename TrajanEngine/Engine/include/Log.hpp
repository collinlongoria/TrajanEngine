#ifndef LOG_HPP
#define LOG_HPP

// Severity levels
enum class Severity {
	GOOD,
	MESSAGE,
	WARNING,
	ERROR
};
constexpr int severity_max = 7; // Used to pad the log after the severity label; Change if needed.

class Log {
public:
	// Retrieve instance
	static Log& Instance();

	// Log Message
	void Output(const std::string& message = "", Severity severity = Severity::MESSAGE);

	// Delete, copy, and move constructors/assignments
	// (Ensures singleton)
	Log(const Log&) = delete;
	Log(Log&&) = delete;
	Log& operator=(const Log&) = delete;
	Log& operator=(Log&&) = delete;

private:
	Log();
	~Log();

	// Returns current timestamp
	std::string GetTime();

	// Output file stream
	std::ofstream file;

	// Ensures thread safe operations
	std::mutex mutex;

	// Start time
	std::chrono::steady_clock::time_point start_time;
};

// Helper function for quicker logging
inline void Output(const std::string& message = "", Severity severity = Severity::MESSAGE) {
	Log::Instance().Output(message, severity);
}

#endif // !LOG_HPP
