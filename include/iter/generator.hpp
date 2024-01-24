#pragma once
#include "iter/iterator.hpp"
#include "iter/iterator_traits.hpp"
#include <concepts>
#include <type_traits>

namespace iter {

namespace generator_impl {

template <typename T>
concept number = std::totally_ordered<T> && std::weakly_incrementable<T>;

} // namespace generator_impl

///
template <bool has_to, typename IteratorTraits, generator_impl::number T>
class Generator : public Iterator<
                      IteratorTraits, //
                      Generator<has_to, IteratorTraits, T>> {
public:
    using reference = T;

private:
    T m_from;
    T m_to;
    T m_current;

public:
    constexpr Generator(const T from, const T to)
        : m_from(from)
        , m_to(to)
        , m_current(from) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<reference> {
        if (m_current < m_to) {
            T current = m_current;
            ++m_current;
            return current;
        }

        return nullopt;
    }

    ///
    template <typename Acc, std::invocable<Acc, reference> FoldFn>
    constexpr auto fold(Acc acc, FoldFn fn) -> Acc {
        while (auto value = this->next()) {
            acc = fn(acc, *value);
        }

        return acc;
    }
};

///
template <typename IteratorTraits, generator_impl::number T>
class Generator<false, IteratorTraits, T>
    : public Iterator<IteratorTraits, Generator<false, IteratorTraits, T>> {
public:
    using reference = T;

private:
    T m_from;
    T m_current;

public:
    constexpr explicit Generator(const T from)
        : m_from(from)
        , m_current(from) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<reference> {
        T current = m_current;
        ++m_current;
        return current;
    }

    ///
    template <typename Acc, std::invocable<Acc, reference> FoldFn>
    constexpr auto fold(Acc acc, FoldFn fn) -> Acc = delete;
};

///
template <generator_impl::number T>
[[nodiscard]]
constexpr auto gen(const T from) {
    using Traits = IteratorTraits<T>;
    return Generator<false, Traits, T>(from);
}

///
template <generator_impl::number T>
[[nodiscard]]
constexpr auto gen(const T from, const T to) {
    using Traits = IteratorTraits<T>;
    return Generator<true, Traits, T>(from, to);
}

} // namespace iter
