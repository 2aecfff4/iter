#pragma once
#include "iter/fwd.hpp"
#include "iter/optional.hpp"
#include <concepts>
#include <type_traits>

namespace iter {

///
template <typename IteratorTraits, typename Derived>
class Iterator {
public:
    using reference = reference_t<IteratorTraits>;

private:
    [[nodiscard]]
    constexpr auto self() -> Derived& {
        return static_cast<Derived&>(*this);
    }

    [[nodiscard]]
    constexpr auto self() const -> const Derived& {
        return static_cast<const Derived&>(*this);
    }

public:
    [[nodiscard]]
    constexpr auto next() -> Optional<reference> {
        return this->self().next();
    }

public:
    ///
    template <typename Self>
    [[nodiscard]]
    constexpr auto enumerate(this Self&& self) {
        return Enumerate(std::forward<Self>(self));
    }

    ///
    template <typename Self, std::predicate<reference> PredicateFn>
    [[nodiscard]]
    constexpr auto filter(this Self&& self, PredicateFn&& predicate) {
        return Filter(std::forward<Self>(self), std::forward<PredicateFn>(predicate));
    }

    template <std::predicate<reference> PredicateFn>
    [[nodiscard]]
    constexpr auto find(PredicateFn predicate) -> decltype(this->next()) {
        while (auto n = this->next()) {
            if (predicate(*n)) {
                return n;
            }
        }
        return nullopt;
    }

    ///
    template <typename Acc, std::invocable<Acc, reference> FoldFn>
    constexpr auto fold(Acc acc, FoldFn&& fn) -> Acc {
        return this->self().fold(std::move(acc), std::forward<FoldFn>(fn));
    }

    ///
    template <std::invocable<reference> ForEachFn>
    constexpr void for_each(ForEachFn fn) {
        while (auto n = this->next()) {
            fn(*n);
        }
    }

    ///
    template <typename Self, std::invocable<reference> MapFn>
    [[nodiscard]]
    constexpr auto map(this Self&& self, MapFn&& map) {
        return Map(std::forward<Self>(self), std::forward<MapFn>(map));
    }

public:
    // /// #TODO:
    // [[nodiscard]]
    // constexpr auto to_cpp() -> CppIterator<Iterator<T, Self>>;

public:
    ///
    template <template <typename, typename...> typename To>
    [[nodiscard]]
    constexpr auto collect();
};

} // namespace iter
