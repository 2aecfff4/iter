#include "iter/concepts.hpp"
#include "iter/enumerate.hpp"
#include "iter/filter.hpp"
#include "iter/generator.hpp"
#include "iter/iterator.hpp"
#include "iter/map.hpp"
#include "iter/vector.hpp"
#include <print>
#include <vector>

namespace examples {

constexpr auto generator() -> iter::iterator auto {
    return iter::gen(0, 16) //
        .filter([](const int& i) { return (i % 2) == 0; })
        .map([](const int& i) { return (float)i + 0.1f; });
}

constexpr auto enumerate() -> iter::iterator auto {
    return iter::gen(0, 16) //
        .enumerate()
        .filter([](const auto& t) {
            const auto& [idx, v] = t;
            return (v % 2) == 0;
        });
}

} // namespace examples

int main() {
    {
        std::println("--examples::generator--");
        auto i = examples::generator();
        while (auto v = i.next()) {
            std::println("{}", *v);
        }
    }

    {
        std::println("--examples::enumerate--");
        auto i = examples::enumerate();
        while (auto t = i.next()) {
            const auto& [idx, v] = *t;
            std::println("{}: {}", idx, v);
        }
    }
}