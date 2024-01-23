#include "concepts.hpp"
#include "filter.hpp"
#include "generator.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

namespace examples {

constexpr auto generator() -> iter::iterator auto {
    return iter::gen(0, 16) //
        .filter([](const int& i) { return (i % 2) == 0; })
        .map([](const int& i) { return (float)i + 0.1f; });
}

} // namespace examples

int main() {
    {
        auto g = examples::generator();
        //
    }
}