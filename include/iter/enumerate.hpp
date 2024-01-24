#pragma once
#include "iter/concepts.hpp"
#include "iter/fwd.hpp"
#include "iter/iterator.hpp"
#include "iter/iterator_traits.hpp"
#include "iter/optional.hpp"
#include "iter/traits.hpp"
#include <tuple>
#include <type_traits>
#include <utility>

namespace iter {

namespace enumerate_impl {

///
template <iterator I>
using reference_t = typename std::tuple<std::size_t, reference_t<I>>;

} // namespace enumerate_impl

///
template <iterator I>
class [[nodiscard]] Enumerate
    : public Iterator<IteratorTraits<enumerate_impl::reference_t<I>>, Enumerate<I>> {
public:
    using reference = enumerate_impl::reference_t<I>;

private:
    I m_base;
    std::size_t m_count = 0;

public:
    constexpr explicit Enumerate(I base)
        : m_base(std::move(base)) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<reference> {
        const std::size_t i = m_count;
        ++m_count;

        return m_base //
            .next()
            .transform([i](reference_t<I> value) { return reference(i, value); });
    }

    ///
    template <typename Acc, std::invocable<Acc, reference> FoldFn>
    constexpr auto fold(Acc acc, FoldFn fn) -> Acc {
        std::size_t index = m_count;
        return m_base.fold(
            acc, //
            [index, fn](const Acc acc, reference_t<I> value) mutable {
                Acc result = fn(acc, reference(index, value));
                ++index;
                return result;
            }
        );
    }
};

///
template <iterator I>
Enumerate(I&&) -> Enumerate<std::decay_t<I>>;

} // namespace iter
