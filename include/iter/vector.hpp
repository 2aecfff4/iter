#pragma once
#include "iter/iterator.hpp"
#include "iter/iterator_traits.hpp"
#include <type_traits>
#include <vector>

namespace iter {

///
template <typename IteratorTraits, typename Container, typename Ref>
class VecIterator
    : public Iterator<IteratorTraits, VecIterator<IteratorTraits, Container, Ref>> {
public:
    using reference = Ref;
    static constexpr bool has_for_each = false;

private:
    Container* m_container;
    std::size_t m_cursor = 0;

public:
    constexpr explicit VecIterator(Container* container)
        : m_container(container) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<reference> {
        if (m_cursor < m_container->size()) {
            const std::size_t cursor = m_cursor;
            m_cursor += 1;
            return (*m_container)[cursor];
        }
        return nullopt;
    }

    ///
    template <typename Acc, std::invocable<Acc, reference> FoldFn>
    constexpr auto fold(Acc acc, FoldFn fn) -> Acc {
        for (auto& value : *m_container) {
            acc = fn(acc, value);
        }

        return acc;
    }
};

///
template <typename T, typename Allocator>
[[nodiscard]]
constexpr auto iter(std::vector<T, Allocator>& vec) {
    using Vec = std::vector<T, Allocator>;
    using Ref = typename Vec::reference;
    return VecIterator<IteratorTraits<Ref>, Vec, Ref>(&vec);
}

///
template <typename T, typename Allocator>
[[nodiscard]]
constexpr auto iter(const std::vector<T, Allocator>& vec) {
    using Vec = const std::vector<T, Allocator>;
    using Ref = typename Vec::const_reference;
    return VecIterator<IteratorTraits<Ref>, Vec, Ref>(&vec);
}

} // namespace iter
