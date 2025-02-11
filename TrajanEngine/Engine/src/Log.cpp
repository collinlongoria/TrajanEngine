#include "stdafx.hpp"

#include "Log.hpp"

Log& Log::Instance() {
	static Log instance;
	return instance;
}

Log::Log() {
	// Open the log file
	file.open("Log.txt", std::ofstream::out | std::ofstream::trunc);
	if (!file.is_open()) {
		std::print("Failed to open log file.");
	}

	// Retrieve starting time
	start_time = std::chrono::steady_clock::now();
}

Log::~Log() {
	// Reset console (if needed)
	std::print("\033[37m");

	if (file.is_open()) {
		file.close();
	}
}

void Log::Output(const std::string& message, Severity severity) {
	// Let only one thread write at a time
	std::lock_guard<std::mutex> lock(mutex);

	// Severity configuration
	std::string severity_str;
	std::string color_str = "\033[37m";
	switch (severity) {
	case Severity::GOOD:
		color_str = "\033[32m";
		severity_str = "GOOD";
		break;
	case Severity::MESSAGE:
		// Color remains default
		severity_str = "MESSAGE";
		break;
	case Severity::WARNING:
		color_str = "\033[33m";
		severity_str = "WARNING";
		break;
	case Severity::ERROR:
		color_str = "\033[31m";
		severity_str = "ERROR";
		break;
	}

	// Timestamp step
	const std::string timestamp_str = GetTime();

	// Final string
	std::string padding(((severity_max - severity_str.size()) / 2), ' ');
	std::string log_str = "[" + timestamp_str + "]""[" + padding + severity_str + padding + "] " + message;

	// Debug only: print to console
#ifdef _DEBUG
	std::print("{}{}\n", color_str, log_str);
#endif

	// Write to log file
	if (file.is_open()) {
		file << log_str << "\n";
	}

}

std::string Log::GetTime() {
	using namespace std::chrono;

	auto now = system_clock::now();
	std::time_t now_t = system_clock::to_time_t(now);

	std::tm local_time;
#ifdef _WIN32
	localtime_s(&local_time, &now_t);
#else
	localtime_r(&now_t, &local_time);
#endif

	// (Format is HH:MM:SS)
	char buffer[9];
	std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &local_time);

	// Calculate elapsed time
	// (Format is HH:MM:SS.mmm)
	auto elapsed = duration_cast<milliseconds>(steady_clock::now() - start_time);
	int elapsed_hours = static_cast<int>(elapsed.count()) / 3600000;
	int elapsed_minutes = (elapsed.count() % 3600000) / 60000;
	int elapsed_seconds = (elapsed.count() % 60000) / 1000;
	int elapsed_milliseconds = elapsed.count() % 1000;

	// Format elapsed time
	char elapsed_buffer[16];
	std::snprintf(elapsed_buffer, sizeof(elapsed_buffer), "%02d:%02d:%02d.%03d", elapsed_hours, elapsed_minutes, elapsed_seconds, elapsed_milliseconds);

	return std::string(buffer) + "|" + elapsed_buffer;
}