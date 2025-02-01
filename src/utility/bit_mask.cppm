export module void_engine.utility.bit_mask;

import std;

export namespace void_engine::utility {

template<typename T>
class BitMask {
public:
	static_assert(std::is_enum_v<T>, "T must be an enum type");

	BitMask(const BitMask& other) : _value(other._value) {}

	BitMask(BitMask&& other) noexcept : _value(other._value) { other._value = 0; }

	auto operator=(const BitMask& other) -> BitMask& {
		if (this == &other) {
			return *this;
		}
		_value = other._value;
		return *this;
	}

	auto operator=(BitMask&& other) noexcept -> BitMask& {
		if (this == &other) {
			return *this;
		}
		_value = other._value;
		other._value = 0;
		return *this;
	}

	BitMask() = default;

	explicit BitMask(T value) : _value(static_cast<std::underlying_type_t<T>>(value)) {}

	explicit BitMask(std::underlying_type_t<T> value) : _value(value) {}

	~BitMask() = default;

	void set(T flag) { _value |= static_cast<std::underlying_type_t<T>>(flag); }

	void unset(T flag) { _value &= ~static_cast<std::underlying_type_t<T>>(flag); }

	void set(T flag, bool value) {
		if (value) {
			set(flag);
		} else {
			unset(flag);
		}
	}

	void toggle(T flag) { _value ^= static_cast<std::underlying_type_t<T>>(flag); }

	void clear() { _value = 0; }

	[[nodiscard]]
	auto is_set(T flag) const -> bool {
		return (_value & static_cast<std::underlying_type_t<T>>(flag)) != 0;
	}

	[[nodiscard]]
	auto get() const -> std::underlying_type_t<T> {
		return _value;
	}

	auto operator=(T value) -> BitMask& {
		_value = static_cast<std::underlying_type_t<T>>(value);
		return *this;
	}

	auto operator|=(T flag) -> BitMask& {
		set(flag);
		return *this;
	}

	auto operator&=(T flag) -> BitMask& {
		unset(flag);
		return *this;
	}

	auto operator^=(T flag) -> BitMask& {
		toggle(flag);
		return *this;
	}

	auto operator|(T flag) const -> BitMask {
		BitMask result = *this;
		result.set(flag);
		return result;
	}

	auto operator&(T flag) const -> BitMask {
		BitMask result = *this;
		result._value &= static_cast<std::underlying_type_t<T>>(flag);
		return result;
	}

	auto operator^(T flag) const -> BitMask {
		BitMask result = *this;
		result.toggle(flag);
		return result;
	}

	explicit operator bool() const { return _value != 0; }

	auto operator==(const BitMask& other) const -> bool { return _value == other._value; }

	auto operator!=(const BitMask& other) const -> bool { return _value != other._value; }

private:
	std::underlying_type_t<T> _value = 0;
};

} // namespace void_engine::utility
