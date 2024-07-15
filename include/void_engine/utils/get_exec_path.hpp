#ifndef VOID_ENGINE_UTILS_GET_EXEC_PATH_HPP
#define VOID_ENGINE_UTILS_GET_EXEC_PATH_HPP

#include <filesystem>

namespace void_engine::utils {

auto get_exec_path() -> std::filesystem::path;

}

#endif // !VOID_ENGINE_UTILS_GET_EXEC_PATH_HPP
