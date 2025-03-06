module void_engine.utility.read_bytes;

import std;

namespace void_engine::utility {

auto read_bytes(const std::filesystem::path& path) -> std::optional<std::vector<std::byte>> {
	auto file = std::ifstream{path, std::ios::binary};
	if (!file.is_open()) return std::nullopt;
	file.seekg(0, std::ios::end);
	const auto size = file.tellg();
	if (size == -1) return std::nullopt;
	file.seekg(0, std::ios::beg);
	auto bytes = std::vector<std::byte>{static_cast<std::size_t>(size)};
	if (!file.read(std::bit_cast<char*>(bytes.data()), size)) return std::nullopt;
	return bytes;
}

}  // namespace void_engine::utility
