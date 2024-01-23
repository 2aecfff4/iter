#pragma once
#include "iter/concepts.hpp"
#include "iter/fwd.hpp"
#include "iter/iterator.hpp"
#include "iter/optional.hpp"
#include <type_traits>
#include <utility>

namespace iter {

namespace filter_impl {

///
template <iterator I, std::predicate<typename I::Type> PredicateFn>
class FilterIterator : I {
public:
    using Traits = typename I::Traits;
    using Type = typename Traits::Type;

private:
    PredicateFn m_predicate;

public:
    ///
    constexpr FilterIterator(I&& i, PredicateFn&& predicate) noexcept
        : I(std::move(i))
        , m_predicate(std::move(predicate)) {}

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<Type> {
        return I::find(m_predicate);
    }
};

} // namespace filter_impl

///
template <iterator I, std::predicate<typename I::Type&> PredicateFn>
class [[nodiscard]] Filter
    : public Iterator<typename I::Traits, filter_impl::FilterIterator<I, PredicateFn>> {
    using Base = Iterator<typename I::Traits, filter_impl::FilterIterator<I, PredicateFn>>;
    using FilterIterator = filter_impl::FilterIterator<I, PredicateFn>;

public:
    ///
    constexpr Filter(I i, PredicateFn predicate) noexcept
        : Base(FilterIterator(std::move(i), std::move(predicate))) {}
};

///
template <iterator I, std::predicate<typename I::Type&> PredicateFn>
Filter(I&&, PredicateFn&&) -> Filter<std::decay_t<I>, std::decay_t<PredicateFn>>;

} // namespace iter
