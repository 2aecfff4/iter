#pragma once
#include "optional.hpp"
#include <concepts>
#include <type_traits>

namespace iter {

///
template <typename I>
concept iterator = requires(I i) {
    typename I::Type;
    { i.next() } -> std::same_as<Optional<typename I::Type>>;
};

} // namespace iter