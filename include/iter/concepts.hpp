#pragma once
#include "iter/optional.hpp"
#include "iter/traits.hpp"

namespace iter {

///
template <typename O>
concept optional = true; // #TODO:

///
template <typename I>
concept iterator = requires(I i) {
    typename reference_t<I>;
    { i.next() };
};

} // namespace iter
