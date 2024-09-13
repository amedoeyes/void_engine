#ifndef VOID_ENGINE_UTILITY_LOGGER_HPP
#define VOID_ENGINE_UTILITY_LOGGER_HPP

#include <cstdint>
#include <format>
#include <iostream>
#include <string_view>

namespace void_engine::utility {

enum class LogLevel : std::uint8_t {
	debug,
	info,
	warning,
	error,
	none,
};

class Logger {
public:
	template <typename... Args>
	static void debug(std::string_view fmt, Args&&... args) {
		log(LogLevel::debug, fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void info(std::string_view fmt, Args&&... args) {
		log(LogLevel::info, fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void warning(std::string_view fmt, Args&&... args) {
		log(LogLevel::warning, fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void error(std::string_view fmt, Args&&... args) {
		log(LogLevel::error, fmt, std::forward<Args>(args)...);
	}

	static void set_log_level(LogLevel log_level) {
		_log_level = log_level;
	}

private:
	static inline LogLevel _log_level = LogLevel::info;

	template <typename... Args>
	static void log(LogLevel level, std::string_view fmt, Args&&... args) {
		if (level < _log_level) {
			return;
		}
		std::string_view prefix;
		switch (level) {
			using enum LogLevel;
			case debug: prefix = "[DEBUG]"; break;
			case info: prefix = "[INFO]"; break;
			case warning: prefix = "[WARNING]"; break;
			case error: prefix = "[ERROR]"; break;
			default:;
		}
		if (level >= LogLevel::warning) {
			std::cerr << prefix << ": " << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
		} else {
			std::cout << prefix << ": " << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
		}
	}
};

} // namespace void_engine::utility

#endif // !VOID_ENGINE_UTILITY_LOGGER_HPP
