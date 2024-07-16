#include "void_engine/utility/logger.hpp"

namespace void_engine::utility {

LogLevel Logger::_log_level = LogLevel::info;

void Logger::set_log_level(LogLevel log_level) {
	_log_level = log_level;
}

} // namespace void_engine::utility
