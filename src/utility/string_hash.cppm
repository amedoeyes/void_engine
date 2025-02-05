export module void_engine.utility.string_hash;

import std;

export namespace void_engine::utility {

struct string_hash {
	using is_transparent = void;

	[[nodiscard]]
	auto operator()(const char* txt) const -> std::size_t {
		return std::hash<std::string_view>{}(txt);
	}

	[[nodiscard]]
	auto operator()(std::string_view txt) const -> std::size_t {
		return std::hash<std::string_view>{}(txt);
	}

	[[nodiscard]]
	auto operator()(const std::string& txt) const -> std::size_t {
		return std::hash<std::string>{}(txt);
	}
};

} // namespace void_engine::utility
