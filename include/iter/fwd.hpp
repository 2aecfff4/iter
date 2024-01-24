#pragma once
#include "iter/concepts.hpp"
#include "iter/traits.hpp"

namespace iter {

///
template <typename IteratorTraits, typename Derived>
class [[nodiscard]] Iterator;

///
template <iterator I>
class [[nodiscard]] Enumerate;

///
template <iterator I, std::predicate<reference_t<I>> PredicateFn>
class [[nodiscard]] Filter;

///
template <iterator I, std::invocable<reference_t<I>> MapFn>
class [[nodiscard]] Map;

///
template <iterator I>
class [[nodiscard]] CppIterator;

} // namespace iter
