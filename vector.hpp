#pragma once
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include <vector>


namespace iter {

namespace vector_impl {

///
template <typename T, typename Container>
class VecIteratorAdaptor {
private:
    Container* m_container;
    std::size_t m_cursor = 0;

public:
    explicit VecIteratorAdaptor(Container* container)
        : m_container(container) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<T> {
        if (m_cursor < m_container->size()) {
            const std::size_t cursor = m_cursor;
            m_cursor += 1;
            return (*m_container)[cursor];
        }
        return nullopt;
    }
};

} // namespace vector_impl

///
template <typename T, typename Allocator>
[[nodiscard]]
constexpr auto iter(std::vector<T, Allocator>& vec) {
    using namespace vector_impl;

    using reference = typename std::vector<T, Allocator>::reference;
    using Traits = IteratorTraits<reference>;
    using Type
        = Iterator<Traits, VecIteratorAdaptor<reference, std::vector<T, Allocator>>>;

    return Type(VecIteratorAdaptor<reference, std::vector<T, Allocator>>(&vec));
}

///
template <typename T, typename Allocator>
[[nodiscard]]
constexpr auto iter(const std::vector<T, Allocator>& vec) {
    using namespace vector_impl;

    using reference = typename std::vector<T, Allocator>::const_reference;
    using Traits = IteratorTraits<reference>;
    using Type
        = Iterator<Traits, VecIteratorAdaptor<reference, const std::vector<T, Allocator>>>;

    return Type(VecIteratorAdaptor<reference, const std::vector<T, Allocator>>(&vec));
}

} // namespace iter
