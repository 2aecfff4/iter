// #pragma once
// #include "filter.hpp"
// #include <concepts>
// #include <type_traits>

// namespace iter {

// // ///
// // template <typename T, typename Self>
// // constexpr auto Iterator<T, Self>::self() -> Self& {
// //     return static_cast<Self&>(*this);
// // }

// // ///
// // template <typename T, typename Self>
// // constexpr auto Iterator<T, Self>::self() const -> const Self& {
// //     return static_cast<const Self&>(*this);
// // }

// // ///
// // template <typename T, typename Self>
// // constexpr auto Iterator<T, Self>::next() -> optional<Type> {
// //     return this->self().next();
// //     // return m_self.next();
// // }

// // ///
// // template <typename T, typename Self>
// // template <typename PredicateFn>
// // constexpr auto Iterator<T, Self>::find(PredicateFn predicate) -> optional<Type>
// // requires(std::predicate<PredicateFn, Type>)
// // {
// //     while (auto n = this->next()) {
// //         if (predicate(*n)) {
// //             return n;
// //         }
// //     }
// //     return nullopt;
// // }

// // template <typename T, typename Self>
// // template <typename ForEachFn>
// // constexpr void Iterator<T, Self>::for_each(ForEachFn fn)
// // requires(std::invocable<ForEachFn, Type>)
// // {
// //     while (auto n = this->next()) {
// //         fn(*n);
// //     }
// // }

// // ///
// // template <typename T, typename Self>
// // template <typename PredicateFn>
// // constexpr auto Iterator<T, Self>::filter(PredicateFn&& predicate)
// //     -> Filter<Iterator<T, Self>, std::decay_t<PredicateFn>>
// // requires(std::predicate<PredicateFn, Type>)
// // {
// //     return Filter(*this, std::forward<PredicateFn>(predicate));
// // }

// // ///
// // template <typename T, typename Self>
// // template <typename Acc, typename FoldFn>
// // constexpr auto Iterator<T, Self>::fold(Acc acc, FoldFn&& fn) -> Acc
// // requires(std::invocable<FoldFn, Acc, Type>)
// // {
// //     // #TODO: Implementation of `fold` depends on the undelying iterator.
// //     return this->self().fold(std::move(acc), std::forward<FoldFn>(fn));
// //     return 0;
// // }

// } // namespace iter
