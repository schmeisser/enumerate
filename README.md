# enumerate
A enumerating iterator to write range-based for loops similar to Python's enumerate.

The `enumerate` function takes a range (anything with `begin()` and `end()` members,
e.g. a container) and returns an enumerated range. This means the resulting iterators
return a pair consisting of:
- the 0-based index of an element,
- a reference to the element the original iterator refers to.

This is especially useful in combination with C++11 range-based for loops and using
C++17 structured bindings on the resulting pair. It can be used to write Python-style
loops like this:
```cpp
std::vector<int> primes = {2, 3, 5, 7, 11, 13};
for (auto [i, p] : enumerate(primes))
    std::cout << "Prime " << i+1 << ": " << p << "\n";
```
Output:
```
Prime 1: 2
Prime 2: 3
Prime 3: 5
Prime 4: 7
Prime 5: 11
Prime 6: 13
```
