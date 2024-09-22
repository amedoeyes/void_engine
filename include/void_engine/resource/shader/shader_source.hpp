#ifndef VOID_ENGINE_RESOURCE_SHADER_SHADER_SOURCE_HPP
#define VOID_ENGINE_RESOURCE_SHADER_SHADER_SOURCE_HPP

#include "void_engine/resource/shader/enums.hpp"

#include <filesystem>
#include <string>
#include <variant>

namespace void_engine::resource::shader {

struct ShaderSource {
	Type type;
	Format format;
	std::variant<std::filesystem::path, std::string> data;
};

} // namespace void_engine::resource::shader

#endif // !VOID_ENGINE_RESOURCE_SHADER_SHADER_SOURCE_HPP
