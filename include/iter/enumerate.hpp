#pragma once
#include "iter/concepts.hpp"
#include "iter/fwd.hpp"
#include "iter/iterator.hpp"
#include "iter/optional.hpp"
#include <tuple>
#include <type_traits>
#include <utility>

namespace iter {

namespace enumerate_impl {

///
template <typename IteratorTraits, iterator I>
class EnumerateIterator : I {
public:
    using Traits = IteratorTraits;
    using Type = typename Traits::Type;

private:
    std::size_t m_count = 0;

public:
    ///
    explicit constexpr EnumerateIterator(I&& i) noexcept
        : I(std::move(i)) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<Type> {
        const std::size_t i = m_count;
        m_count += 1;
        return I::next() //
            .transform([i]<typename T>(T&& v) -> Type {
                return Type(i, std::forward<T>(v));
            });
    }
};

template <iterator I>
struct EnumerateIteratorTraits {
    using Type = std::tuple<std::size_t, typename I::Type>;
};

} // namespace enumerate_impl

///
template <iterator I>
class [[nodiscard]] Enumerate
    : public Iterator<
          enumerate_impl::EnumerateIteratorTraits<I>,
          enumerate_impl::EnumerateIterator<enumerate_impl::EnumerateIteratorTraits<I>, I>> {
    using Base = Iterator<
        enumerate_impl::EnumerateIteratorTraits<I>,
        enumerate_impl::EnumerateIterator<enumerate_impl::EnumerateIteratorTraits<I>, I>>;
    using MapIterator
        = enumerate_impl::EnumerateIterator<enumerate_impl::EnumerateIteratorTraits<I>, I>;

public:
    ///
    explicit constexpr Enumerate(I i) noexcept
        : Base(MapIterator(std::move(i))) {}
};

///
template <iterator I>
Enumerate(I&&) -> Enumerate<std::decay_t<I>>;

} // namespace iter
