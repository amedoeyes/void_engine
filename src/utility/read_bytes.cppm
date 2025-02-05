export module void_engine.utility.read_bytes;

import std;

export namespace void_engine::utility {

auto read_bytes(const std::filesystem::path& path) -> std::optional<std::vector<std::byte>>;

}  // namespace void_engine::utility
