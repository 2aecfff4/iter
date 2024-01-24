#pragma once
#include <type_traits>

namespace iter {

///
template <typename T>
using reference_t = typename std::remove_cvref_t<T>::reference;

} // namespace iter
