#pragma once
#include "fwd.hpp"
#include "optional.hpp"
#include <concepts>
#include <type_traits>

namespace iter {

///
template <typename T, typename Self>
class [[nodiscard]] Iterator : Self {
private:

public:
    ///
    // using Type = typename T::value_type;
    using Type = int;

public:
    constexpr explicit Iterator(Self self)
        : Self(std::move(self)) {
    }

private:
    // template <typename Selfs>
    // void self(this Selfs&& s) {
    // }

    [[nodiscard]]
    constexpr auto self() -> Self&;

    [[nodiscard]]
    constexpr auto self() const -> const Self&;

public:
    ///
    [[nodiscard]]
    constexpr auto next() -> optional<Type>;

public:
    ///
    template <typename PredicateFn>
    [[nodiscard]]
    constexpr auto filter(PredicateFn&& predicate)
        -> Filter<Iterator<T, Self>, PredicateFn>
    requires(std::predicate<PredicateFn, Type>);

    ///
    template <typename PredicateFn>
    [[nodiscard]]
    constexpr auto find(PredicateFn predicate) -> optional<Type>
    requires(std::predicate<PredicateFn, Type>);

    ///
    template <typename ForEachFn>
    constexpr void for_each(ForEachFn fn)
    requires(std::invocable<ForEachFn, Type>);

    ///
    template <typename Acc, typename FoldFn>
    constexpr auto fold(Acc acc, FoldFn&& fn) -> Acc
    requires(std::invocable<FoldFn, Acc, Type>);

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

#include "iterator.tpp"
