#ifndef VOID_ENGINE_EVENT_TYPES_HPP
#define VOID_ENGINE_EVENT_TYPES_HPP

#include <cstdint>
#include <functional>

namespace void_engine::event {

template <typename T>
using Callback = std::function<void(const T&)>;

using EventID = uint32_t;

} // namespace void_engine::event

#endif // !VOID_ENGINE_EVENT_TYPES_HPP
