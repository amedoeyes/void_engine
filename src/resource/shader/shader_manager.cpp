#include "void_engine/resource/shader/shader_manager.hpp"

#include "void_engine/resource/shader/shader.hpp"

#include <cassert>
#include <filesystem>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace void_engine::resource::shader {

ShaderManager::ShaderManager(std::filesystem::path root_path) : _root_path(std::move(root_path)) {
}

ShaderManager::~ShaderManager() {
	for (auto& [_, shader] : _shaders) {
		delete shader;
	}
}

auto ShaderManager::create(std::string_view name) -> Shader& {
	assert(_shaders.find(name.data()) == _shaders.end() && "Shader already exists");
	auto [it, _] = _shaders.emplace(name.data(), new Shader(_root_path));
	return *(it->second);
}

void ShaderManager::destroy(std::string_view name) {
	const auto it = _shaders.find(name.data());
	assert(it != _shaders.end() && "Shader does not exist");
	delete it->second;
	_shaders.erase(it);
}

auto ShaderManager::get(std::string_view name) -> Shader& {
	const auto it = _shaders.find(name.data());
	assert(it != _shaders.end() && "Shader does not exist");
	return *(it->second);
}

void ShaderManager::set_root_path(const std::filesystem::path& root_path) {
	_root_path = root_path;
	for (auto& [_, shader] : _shaders) {
		shader->set_root_path(_root_path);
	}
}

} // namespace void_engine::resource::shader
