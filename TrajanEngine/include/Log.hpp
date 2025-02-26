#ifndef LOG_HPP
#define LOG_HPP

#include <mutex>
#include <fstream>
#include <chrono>
#include <string>

#include "EngineAPI.hpp"

// Severity levels
enum class Severity {
	GOOD,
	MESSAGE,
	WARNING,
	ERROR
};
constexpr int severity_max = 7; // Used to pad the log after the severity label; Change if needed.

class ENGINE_API Log {
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
inline ENGINE_API void Output(const std::string& message = "", Severity severity = Severity::MESSAGE) {
	Log::Instance().Output(message, severity);
}

#endif // !LOG_HPP
