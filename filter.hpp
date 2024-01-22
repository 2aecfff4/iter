#pragma once
#include "concepts.hpp"
#include "fwd.hpp"
#include "iterator.hpp"
#include "optional.hpp"
#include <utility>

namespace iter {

namespace filter_impl {

///
template <iterator I, std::predicate<typename I::Type&> PredicateFn>
class FilterIterator : I {
private:
    PredicateFn m_predicate;

public:
    ///
    constexpr FilterIterator(I i, PredicateFn&& predicate) noexcept
        : I(std::move(i))
        , m_predicate(std::move(predicate)) {
    }

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> optional<int> {
        return I::find(m_predicate);
    }
};

} // namespace filter_impl

///
template <iterator I, std::predicate<typename I::Type&> PredicateFn>
class [[nodiscard]] Filter
    : public Iterator<typename I::Type, filter_impl::FilterIterator<I, PredicateFn>> {
    // : public IteratorWrapper<typename I::Type, I, Filter<I, PredicateFn>> {
    // // , public Iterator<typename I::Type, Filter>
    // using Base = IteratorWrapper<typename I::Type, I, Filter<I, PredicateFn>>;
    using Base = Iterator<typename I::Type, filter_impl::FilterIterator<I, PredicateFn>>;

private:
    // I m_parent;
    // PredicateFn m_predicate;

public:
    ///
    constexpr Filter(I i, PredicateFn&& predicate) noexcept
        // Base(std::move(i))
        //,
        // m_parent(std::move(i))
        // , m_predicate(std::move(predicate))
        : Base(filter_impl::FilterIterator<I, PredicateFn>(
            std::move(i), std::move(predicate)
        )) {
    }

    // public:
    //     ///
    //     [[nodiscard]]
    //     constexpr auto next() -> optional<int>;
};

} // namespace iter

#include "filter.tpp"
