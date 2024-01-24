#pragma once
#include "iter/concepts.hpp"
#include "iter/fwd.hpp"
#include "iter/iterator.hpp"
#include "iter/iterator_traits.hpp"
#include "iter/optional.hpp"
#include <type_traits>
#include <utility>

namespace iter {

///
template <iterator I, std::invocable<reference_t<I>> MapFn>
class [[nodiscard]] Map : public Iterator<
                              IteratorTraits<std::invoke_result_t<MapFn, reference_t<I>>>,
                              Map<I, MapFn>> {
public:
    using reference = std::invoke_result_t<MapFn, reference_t<I>>;

private:
    I m_base;
    MapFn m_map;

public:
    constexpr Map(I base, MapFn map)
        : m_base(std::move(base))
        , m_map(std::move(map)) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<reference> {
        return m_base.next().transform(m_map);
    }

    ///
    template <typename Acc, std::invocable<Acc, reference> FoldFn>
    constexpr auto fold(Acc acc, FoldFn fn) -> Acc {
        return m_base.fold(
            acc, //
            [&](const Acc acc, reference_t<I> value) { return fn(acc, m_map(value)); }
        );
    }
};

///
template <iterator I, std::invocable<reference_t<I>> MapFn>
Map(I&&, MapFn&&) -> Map<std::decay_t<I>, std::decay_t<MapFn>>;

} // namespace iter
