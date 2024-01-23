#pragma once
#include "concepts.hpp"
#include "fwd.hpp"
#include "iterator.hpp"
#include "optional.hpp"
#include <type_traits>
#include <utility>

namespace iter {

namespace map_impl {

///
template <typename IteratorTraits, iterator I, std::invocable<typename I::Type> MapFn>
class MapIterator : I {
public:
    using Traits = IteratorTraits;
    using Type = typename Traits::Type;

private:
    MapFn m_map;

public:
    ///
    constexpr MapIterator(I&& i, MapFn&& map) noexcept
        : I(std::move(i))
        , m_map(std::move(map)) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<Type> {
        return I::next().transform(m_map);
    }
};

template <iterator I, std::invocable<typename I::Type> MapFn>
struct MapIteratorTraits {
    using Type = std::invoke_result_t<MapFn, typename I::Type>;
};

} // namespace map_impl

///
template <iterator I, std::invocable<typename I::Type> MapFn>
class [[nodiscard]] Map
    : public Iterator<
          map_impl::MapIteratorTraits<I, MapFn>,
          map_impl::MapIterator<map_impl::MapIteratorTraits<I, MapFn>, I, MapFn>> {
    using Base = Iterator<
        map_impl::MapIteratorTraits<I, MapFn>,
        map_impl::MapIterator<map_impl::MapIteratorTraits<I, MapFn>, I, MapFn>>;
    using MapIterator
        = map_impl::MapIterator<map_impl::MapIteratorTraits<I, MapFn>, I, MapFn>;

public:
    ///
    constexpr Map(I i, MapFn map) noexcept
        : Base(MapIterator(std::move(i), std::move(map))) {}
};

///
template <iterator I, std::predicate<typename I::Type&> PredicateFn>
Map(I&&, PredicateFn&&) -> Map<std::decay_t<I>, std::decay_t<PredicateFn>>;

} // namespace iter
