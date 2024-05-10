#include "void_engine/logger.hpp"

#include <unordered_map>

namespace void_engine {

Logger::LogLevel Logger::_log_level = Logger::LogLevel::info;
std::unordered_map<Logger::LogLevel, std::string_view> Logger::_log_level_map =
	{
		{Logger::LogLevel::debug, "[DEBUG]"},
		{Logger::LogLevel::info, "[INFO]"},
		{Logger::LogLevel::warning, "[WARNING]"},
		{Logger::LogLevel::error, "[ERROR]"},
};

void Logger::set_log_level(LogLevel log_level) {
	_log_level = log_level;
}

}  // namespace void_engine
