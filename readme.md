# iter
An experimental proof-of-concept iterator library aiming to recreate Rust's iterators.


```cpp
int main() {
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    iter::iter(v) 
        .enumerate()
        .filter([](const auto& tuple) { 
            const auto& [idx, value] = tuple;
            return (value % 2) == 0; 
        })
        .for_each([](const auto& tuple) { 
            const auto& [idx, value] = tuple;
            std::println("{}: {}", idx, value);
        });
}
```

# Build
To build, you will need the following:
- Modern C++ compiler that supports C++23
- CMake
