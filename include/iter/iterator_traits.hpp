#pragma once
#include <type_traits>

namespace iter {

///
template <typename Ref>
struct IteratorTraits {
    using reference = Ref;
};

} // namespace iter
