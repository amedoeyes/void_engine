#ifndef VOID_ENGINE_LOGGER_HPP
#define VOID_ENGINE_LOGGER_HPP

#include <format>
#include <iostream>
#include <string_view>
#include <unordered_map>

namespace void_engine {

enum class LogLevel {
	none,
	debug,
	info,
	warning,
	error
};

class Logger {
public:
	Logger(LogLevel log_level = LogLevel::info);

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
	static std::unordered_map<LogLevel, std::string_view> _log_level_map;

private:
	template <typename... Args>
	static void
	log(LogLevel level, const std::string_view fmt, const Args&... args) {
		if (level < _log_level || _log_level == LogLevel::none) return;

		std::string format_str =
			std::vformat(fmt, std::make_format_args(args...));
		std::string_view level_str = _log_level_map.at(level);
		std::string message = std::format("{}: {}\n", level_str, format_str);

		if (level >= LogLevel::warning) {
			std::cerr << message;
		} else {
			std::cout << message;
		}
	}
};

} // namespace void_engine

#endif // !VOID_ENGINE_LOGGER_HPP
