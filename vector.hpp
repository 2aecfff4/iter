#pragma once
#include "iterator.hpp"
#include <vector>

namespace iter {

///
template <typename T, typename Container>
class VecIteratorAdaptor {
private:
    Container* m_container;
    std::size_t m_cursor = 0;

public:
    VecIteratorAdaptor(Container* container)
        : m_container(container) {
    }

    // VecIteratorAdaptor(const VecIteratorAdaptor&) = delete;
    // VecIteratorAdaptor& operator=(const VecIteratorAdaptor&) = delete;

    // VecIteratorAdaptor(VecIteratorAdaptor&&) = default;
    // VecIteratorAdaptor& operator=(VecIteratorAdaptor&&) = default;

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> optional<T> {
        if (m_cursor < m_container->size()) {
            const std::size_t cursor = m_cursor;
            m_cursor += 1;
            return (*m_container)[cursor];
        }
        return nullopt;
    }
};

template <typename T, typename Allocator>
[[nodiscard]]
constexpr auto iter(std::vector<T, Allocator>& vec) {
    using Type = Iterator<
        std::vector<T, Allocator>,
        VecIteratorAdaptor<T&, std::vector<T, Allocator>>>;
    return Type(VecIteratorAdaptor<T&, std::vector<T, Allocator>>(&vec));
}

} // namespace iter
