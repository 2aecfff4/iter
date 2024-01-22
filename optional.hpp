#pragma once
#include <optional>
#include <type_traits>

namespace iter {

///
template <typename T>
using optional = std::conditional_t<
    std::is_reference_v<T>,
    std::optional<std::reference_wrapper<std::remove_reference_t<T>>>,
    std::optional<T>>;

using std::nullopt;

} // namespace iter
