#pragma once
#include "iter/iterator.hpp"
#include "iter/iterator_traits.hpp"
#include "iter/optional.hpp"
#include <concepts>

namespace iter {

namespace generator_impl {

///
template <bool has_to, typename IteratorTraits>
class GeneratorIteratorAdaptor {
public:
    using Traits = IteratorTraits;
    using Type = typename Traits::Type;

private:
    Type m_from;
    Type m_to;
    Type m_current;

public:
    constexpr GeneratorIteratorAdaptor(const Type from, const Type to)
        : m_from(from)
        , m_to(to)
        , m_current(from) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<Type> {
        if (m_current < m_to) {
            const Type current = m_current;
            m_current += 1;
            return current;
        }

        return nullopt;
    }
};

///
template <typename IteratorTraits>
class GeneratorIteratorAdaptor<false, IteratorTraits> {
public:
    using Traits = IteratorTraits;
    using Type = typename Traits::Type;

private:
    Type m_from;
    Type m_current;

public:
    explicit constexpr GeneratorIteratorAdaptor(const Type from)
        : m_from(from)
        , m_current(from) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<Type> {
        const Type current = m_current;
        m_current += 1;
        return current;
    }
};

} // namespace generator_impl

///
template <std::integral T>
[[nodiscard]]
constexpr auto gen(const T from) {
    using namespace generator_impl;

    using Traits = IteratorTraits<T>;
    using GeneratorAdaptor = GeneratorIteratorAdaptor<false, Traits>;
    using Type = Iterator<Traits, GeneratorAdaptor>;

    return Type(GeneratorAdaptor(from));
}

///
template <std::integral T>
[[nodiscard]]
constexpr auto gen(const T from, const T to) {
    using namespace generator_impl;

    using Traits = IteratorTraits<T>;
    using GeneratorAdaptor = GeneratorIteratorAdaptor<true, Traits>;
    using Type = Iterator<Traits, GeneratorAdaptor>;

    return Type(GeneratorAdaptor(from, to));
}

} // namespace iter
