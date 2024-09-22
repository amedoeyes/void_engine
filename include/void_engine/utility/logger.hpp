#ifndef VOID_ENGINE_UTILITY_LOGGER_HPP
#define VOID_ENGINE_UTILITY_LOGGER_HPP

#include <bits/chrono.h>
#include <chrono>
#include <cstdint>
#include <format>
#include <iostream>
#include <mutex>
#include <string>
#include <string_view>
#include <utility>

namespace void_engine::utility::logger {

enum class Level : std::uint8_t {
	none,
	debug,
	info,
	warning,
	error,
};

struct Context {
	Level level = Level::info;
	std::ostream* output = &std::cout;
	std::mutex mutex;
};

static inline auto get_context() -> Context& {
	static Context context;
	return context;
}

inline void set_level(Level level) {
	static Context& context = get_context();
	context.level = level;
}

inline void set_output(std::ostream& output) {
	static Context& context = get_context();
	context.output = &output;
}

template <typename... Args>
void log(Level level, std::string_view fmt, Args&&... args) {
	static Context& context = get_context();
	if (context.level == Level::none || level < context.level) {
		return;
	}
	const std::lock_guard<std::mutex> lock(context.mutex);
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	auto zt = std::chrono::zoned_time{
		std::chrono::current_zone(), std::chrono::floor<std::chrono::seconds>(now)
	};
	const std::string timestamp = std::format("{:%T}.{:03}", zt, ms.count());
	std::string_view prefix;
	switch (level) {
		using enum Level;
		case debug: prefix = "DEBUG"; break;
		case info: prefix = "INFO"; break;
		case warning: prefix = "WARNING"; break;
		case error: prefix = "ERROR"; break;
		default: std::unreachable();
	}
	const std::string message = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
	*context.output << std::format("{}: {}: {}\n", timestamp, prefix, message);
}

template <typename... Args>
void debug(std::string_view fmt, Args&&... args) {
	log(Level::debug, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void info(std::string_view fmt, Args&&... args) {
	log(Level::info, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void warning(std::string_view fmt, Args&&... args) {
	log(Level::warning, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void error(std::string_view fmt, Args&&... args) {
	log(Level::error, fmt, std::forward<Args>(args)...);
}

} // namespace void_engine::utility::logger

#endif // !VOID_ENGINE_UTILITY_LOGGER_HPP
