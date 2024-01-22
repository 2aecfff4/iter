# iter
An experimental proof-of-concept iterator library aiming to recreate Rust's iterators.


```cpp
int main() {
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    iter::iter(v) 
        .filter([](const int& i) { return (i % 2) == 0; })
        .for_each([](const int& v) { std::cout << v << '\n'; });
}
```
