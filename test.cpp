#include "concepts.hpp"
#include "filter.hpp"
#include "iterator.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    iter::iter(v) //
        .filter([](const int& i) { return (i % 2) == 0; })
        .for_each([](const int& v) { std::cout << v << '\n'; });
}
