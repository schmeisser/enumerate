#include "../include/enumerate.h"

#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using iter::enumerate;

// Vector wrapper printing information in destructor
class DebugVector : public vector<double> {
public:
    DebugVector() = default;
    DebugVector(const DebugVector&) = default;
    DebugVector(DebugVector&&) = default;
    ~DebugVector() {
        std::cout << "Dtor of vector with " << size() << " elements. ";
        if (empty())
            std::cout << "Probably a moved-from temporary.";
        std::cout << "\n";
    }
};
// using DebugVector = vector<double>;

DebugVector twice(const DebugVector& v) {
    DebugVector r;
    for (auto& d : v)
        r.push_back(2 * d);
    return r;
}

int main() {
    // Example from README.md
    std::vector<int> primes = {2, 3, 5, 7, 11, 13};
    for (auto [i, p] : enumerate(primes))
        std::cout << "Prime " << i+1 << ": " << p << "\n";

    // Several different ways to call enumerate
    DebugVector v; //(3.5, 4.6, 7.8, 99.);
    v.push_back(3.5);
    v.push_back(4.6);
    v.push_back(7.8);
    v.push_back(99.);
    std::cout << "Original vector:\n";
    for (auto& d : v)
        std::cout << d << "\n";

    std::cout << "enumerate iterator, manually dereferenced:\n";
    auto en = enumerate(v);
    auto c = en.begin();
    auto e = en.end();
    for (; c != e; ++c) {
        auto [i, d] = *c;
        std::cout << i << ", " << d << "\n";
    }

    std::cout << "enumerate iterator, range based loop, modifying v:\n";
    for (auto [i, d] : enumerate(v)) {
        std::cout << i << ", " << d << " -> " << d + 1 << "\n";
        d += 1;
    }

    std::cout << "enumerate iterator, range based loop (modified v):\n";
    for (auto [i, d] : enumerate(v)) {
        std::cout << i << ", " << d << "\n";
    }

    std::cout << "enumerate iterator of lvalue twice(v), range based loop:\n";
    const auto& tv = twice(v);
    for (auto [i, d] : enumerate(tv)) {
        std::cout << i << ", " << d << "\n";
    }

    std::cout << "enumerate iterator of rvalue twice(v), range based loop:\n";
    for (auto [i, d] : enumerate(twice(v))) {
        std::cout << i << ", " << d << "\n";
    }

    std::cout << "twice(v), range based loop:\n";
    for (auto e : twice(v)) {
        std::cout << e << "\n";
    }
}
