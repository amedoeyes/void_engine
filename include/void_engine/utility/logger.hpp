#ifndef VOID_ENGINE_UTILITY_LOGGER_HPP
#define VOID_ENGINE_UTILITY_LOGGER_HPP

#include <cstdint>
#include <format>
#include <iostream>
#include <string>
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
	static void set_log_level(LogLevel log_level);

	template <typename... Args>
	static void debug(const std::string_view fmt, const Args&... args) {
		log(LogLevel::debug, fmt, args...);
	}

	template <typename... Args>
	static void info(const std::string_view fmt, const Args&... args) {
		log(LogLevel::info, fmt, args...);
	}

	template <typename... Args>
	static void warning(const std::string_view fmt, const Args&... args) {
		log(LogLevel::warning, fmt, args...);
	}

	template <typename... Args>
	static void error(const std::string_view fmt, const Args&... args) {
		log(LogLevel::error, fmt, args...);
	}

private:
	static LogLevel _log_level;

	template <typename... Args>
	static void log(LogLevel level, const std::string_view fmt, const Args&... args) {
		if (level < _log_level) {
			return;
		}

		std::string format_str = std::vformat(fmt, std::make_format_args(args...));
		std::string_view level_str;
		switch (level) {
			case LogLevel::debug: level_str = "[DEBUG]"; break;
			case LogLevel::info: level_str = "[INFO]"; break;
			case LogLevel::warning: level_str = "[WARNING]"; break;
			case LogLevel::error: level_str = "[ERROR]"; break;
			default:;
		}
		const std::string message = std::format("{}: {}\n", level_str, format_str);

		if (level >= LogLevel::warning) {
			std::cerr << message;
		} else {
			std::cout << message;
		}
	}
};

} // namespace void_engine::utility

#endif // !VOID_ENGINE_UTILITY_LOGGER_HPP
