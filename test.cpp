#include "concepts.hpp"
#include "filter.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

#include "generator.hpp"

auto example(const std::vector<int>& vec) -> iter::iterator auto {
    auto filter = [](const int& i) { return (i % 2) == 0; };
    return iter::iter(vec) //
        .filter(filter)
        .map([](const int& i) { return (float)i + 0.1f; });
}

int main() {
    const std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    {
        auto i = example(v);
        while (auto v = i.next()) {
            std::cout << *v << '\n';
        }
    }

    iter::iter(v) //
        .filter([](const int& i) { return (i % 2) == 0; })
        .map([](const int& i) { return (float)i + 0.1f; })
        .for_each([](const float& v) { std::cout << v << '\n'; });
}
