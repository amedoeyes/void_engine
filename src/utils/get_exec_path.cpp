#include "void_engine/utils/get_exec_path.hpp"

#include <array>
#include <filesystem>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <unistd.h>
#elif defined(__linux__)
#include <linux/limits.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace void_engine::utils {

auto get_exec_path() -> std::filesystem::path {
#if defined(_WIN32)
	std::array<char, MAX_PATH> buffer{};
	GetModuleFileNameA(nullptr, buffer.data(), buffer.size());
	return buffer.data();
#elif defined(__APPLE__)
	uint32_t size = 0;
	_NSGetExecutablePath(nullptr, &size);
	std::array<char, PATH_MAX> buffer;
	_NSGetExecutablePath(buffer.data(), &buffer_size);
	return buffer.data();
#elif defined(__linux__)
	std::array<char, PATH_MAX> buffer{};
	const ssize_t size = readlink("/proc/self/exe", buffer.data(), buffer.size());
	if (size == -1) {
		return "";
	}
	return buffer.data();
#else
#error "Unsupported platform"
#endif
}

} // namespace void_engine::utils
