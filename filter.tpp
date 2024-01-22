#pragma once
#include <concepts>
#include <type_traits>

namespace iter {

// template <iterator I, std::predicate<typename I::Type&> PredicateFn>
// constexpr auto Filter<I, PredicateFn>::next() -> optional<int> {
//     return this->parent().find(m_predicate);
//     //return I::find(m_predicate);
// }

} // namespace iter
