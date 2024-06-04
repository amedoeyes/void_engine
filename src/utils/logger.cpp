#include "void_engine/utils/logger.hpp"

namespace void_engine::utils {

LogLevel Logger::_log_level = LogLevel::info;

void Logger::set_log_level(LogLevel log_level) {
	_log_level = log_level;
}

} // namespace void_engine::utils
