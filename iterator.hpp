#pragma once
#include "fwd.hpp"
#include "optional.hpp"
#include <concepts>
#include <type_traits>

namespace iter {

///
template <typename IteratorTraits, typename Impl>
class [[nodiscard]] Iterator : Impl {
public:
    using Traits = IteratorTraits;
    using Type = typename Traits::Type;

public:
    constexpr explicit Iterator(Impl self)
        : Impl(std::move(self)) {}

private:
    // template <typename Selfs>
    // void self(this Selfs&& s) {
    // }

    [[nodiscard]]
    constexpr auto self() -> Impl& {
        return static_cast<Impl&>(*this);
    }

    [[nodiscard]]
    constexpr auto self() const -> const Impl& {
        return static_cast<const Impl&>(*this);
    }

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> Optional<Type> {
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
    template <typename Self, std::predicate<Type> PredicateFn>
    [[nodiscard]]
    constexpr auto filter(this Self&& self, PredicateFn&& predicate) {
        return Filter(std::forward<Self>(self), std::forward<PredicateFn>(predicate));
    }

    ///
    template <typename Self, std::invocable<Type> MapFn>
    [[nodiscard]]
    constexpr auto map(this Self&& self, MapFn&& map) {
        return Map(std::forward<Self>(self), std::forward<MapFn>(map));
    }

    ///
    template <std::predicate<Type> PredicateFn>
    [[nodiscard]]
    constexpr auto find(PredicateFn predicate) -> Optional<Type> {
        while (auto n = this->next()) {
            if (predicate(*n)) {
                return n;
            }
        }
        return nullopt;
    }

    ///
    template <std::invocable<Type> ForEachFn>
    constexpr void for_each(ForEachFn fn) {
        while (auto n = this->next()) {
            fn(*n);
        }
    }

    ///
    template <typename Acc, std::invocable<Acc, Type> FoldFn>
    constexpr auto fold(Acc acc, FoldFn&& fn) -> Acc {
        // #TODO: Implementation of `fold` depends on the undelying iterator.
        return this->self().fold(std::move(acc), std::forward<FoldFn>(fn));
        return 0;
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
