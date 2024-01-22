#pragma once
#include "concepts.hpp"

namespace iter {

template <typename T, typename Self>
class [[nodiscard]] Iterator;

///
template <iterator I, std::predicate<typename I::Type&> PredicateFn>
class [[nodiscard]] Filter;

template <iterator I>
class [[nodiscard]] CppIterator;

} // namespace iter
