#include "void_engine/resources/shader_manager.hpp"

#include "void_engine/resources/shader.hpp"

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace void_engine::resources {

std::unordered_map<std::string, Shader*> ShaderManager::_shaders;

void ShaderManager::terminate() {
	for (auto& [_, shader] : _shaders) {
		delete shader;
	}
}

auto ShaderManager::create(const std::string& name) -> Shader* {
	auto it = _shaders.find(name);
	if (it != _shaders.end()) delete it->second;
	auto* shader = new Shader;
	_shaders[name] = shader;
	return shader;
}

void ShaderManager::destroy(const std::string& name) {
	const auto it = _shaders.find(name);
	if (it == _shaders.end())
		throw std::runtime_error("Texture not found: " + name);
	delete it->second;
	_shaders.erase(it);
}

auto ShaderManager::get(const std::string& name) -> Shader* {
	const auto it = _shaders.find(name);
	if (it == _shaders.end())
		throw std::runtime_error("Texture not found: " + name);
	return it->second;
}

} // namespace void_engine::resources
