#ifndef VOID_ENGINE_UTILITY_STRING_HASH_HPP
#define VOID_ENGINE_UTILITY_STRING_HASH_HPP

#include <string>
#include <string_view>

namespace void_engine::utility {

struct string_hash {
	using is_transparent = void;
	[[nodiscard]] auto operator()(const char* txt) const -> size_t {
		return std::hash<std::string_view>{}(txt);
	}
	[[nodiscard]] auto operator()(std::string_view txt) const -> size_t {
		return std::hash<std::string_view>{}(txt);
	}
	[[nodiscard]] auto operator()(const std::string& txt) const -> size_t {
		return std::hash<std::string>{}(txt);
	}
};

} // namespace void_engine::utility

#endif // !VOID_ENGINE_UTILITY_STRING_HASH_HPP
