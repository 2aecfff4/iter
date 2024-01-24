#pragma once
#include "iter/concepts.hpp"
#include "iter/fwd.hpp"
#include "iter/iterator.hpp"
#include "iter/iterator_traits.hpp"
#include "iter/optional.hpp"
#include <concepts>
#include <type_traits>
#include <utility>

namespace iter {

///
template <iterator I, std::predicate<reference_t<I>> FilterFn>
class [[nodiscard]] Filter
    : public Iterator<IteratorTraits<reference_t<I>>, Map<I, FilterFn>> {
public:
    using reference = reference_t<I>;

private:
    I m_base;
    FilterFn m_predicate;

public:
    constexpr Filter(I base, FilterFn predicate)
        : m_base(std::move(base))
        , m_predicate(std::move(predicate)) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<reference> {
        return m_base.find(m_predicate);
    }

    ///
    template <typename Acc, std::invocable<Acc, reference> FoldFn>
    constexpr auto fold(Acc acc, FoldFn fn) -> Acc {
        return m_base.fold(
            acc, //
            [&](const Acc acc, reference_t<I> value) {
                if (m_predicate(value)) {
                    return fn(acc, value);
                }

                return acc;
            }
        );
    }
};

///
template <iterator I, std::predicate<reference_t<I>> FilterFn>
Filter(I&&, FilterFn&&) -> Filter<std::decay_t<I>, std::decay_t<FilterFn>>;

} // namespace iter
