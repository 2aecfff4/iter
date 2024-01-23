#pragma once
#include "iter/concepts.hpp"

namespace iter {

///
template <typename T, typename Self>
class [[nodiscard]] Iterator;

///
template <iterator I>
class [[nodiscard]] Enumerate;

///
template <iterator I, std::predicate<typename I::Type&> PredicateFn>
class [[nodiscard]] Filter;

///
template <iterator I, std::invocable<typename I::Type> MapFn>
class [[nodiscard]] Map;

///
template <iterator I>
class [[nodiscard]] CppIterator;

} // namespace iter
