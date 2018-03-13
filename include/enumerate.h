#ifndef ENUMERATE_H_INCLUDED_32E3C8F6_6B8B_42FA_874C_7008AA033987
#define ENUMERATE_H_INCLUDED_32E3C8F6_6B8B_42FA_874C_7008AA033987

#include <utility>

namespace iter {
template <typename T> class enumerator;

//! Enumerate container / range-expression
/*! The iterators of the returned range produce std::pairs containing
 * - the 0-based index of the element
 * - a reference to the element the original iterator refers to.
 * This is especially useful in combination with C++17 structured bindings in
 * range-based for loops, e.g.:
 *     for (auto [i, v] : enumerate(vec))
 *
 * The argument \a c is stored by reference in enumerator and thus must outlive
 * the enumerator, otherwise the behavior is undefined.
 * \param c The container to enumerate
 * \return A range object of type \class enumerator operating on c.
 */
template <typename T> auto enumerate(T& c) {
    // Lvalue reference, store a reference in the enumerator.
    return enumerator<T&>{c};
}

//! Enumerate container / range-expression
/*! This is an overload for rvalue expressions (temporaries). To allow useful
 * calls like for (auto [i, v] : enumerate(temp_expression)), the temporary is
 * moved to a member of the enumerator to extend its lifetime.
 * This requires \c T to be move-constructible.
 */
template <typename T> auto enumerate(T&& c) {
    // Rvalue reference, move to extend lifetime.
    return enumerator<T>(std::move(c));
}

//! An enumerate_iterator wraps an iterator of type \c It and produces a pair...
/*! of an enumeration index as well as the original element produced by iterator
 * \c It.
 */
template <typename It> class enumerate_iterator {
    size_t idx;
    It it;

public:
    using reference = std::pair<size_t, decltype(*it)>;

    enumerate_iterator(size_t idx, It it) : idx(idx), it(it) {}

    reference operator*() { return reference(idx, *it); }

    enumerate_iterator& operator++() {
        idx++;
        it++;
        return *this;
    }
    enumerate_iterator operator++(int) {
        enumerate_iterator retval = *this;
        ++(*this);
        return retval;
    }
    bool operator==(const enumerate_iterator& other) const {
        return it == other.it;
    }
    bool operator!=(const enumerate_iterator& other) const {
        return !(*this == other);
    }
};

//! Class enumerator wraps a container / range-expression such that the
//! \c begin() and \c end() members create enumerate_iterator's.
template <typename T> class enumerator {
    T c;

public:
    enumerator(std::remove_reference_t<T>& c) : c(c) {}
    enumerator(std::remove_reference_t<T>&& c) : c(std::move(c)) {}
    ~enumerator() = default;

    auto begin() {
        return enumerate_iterator<decltype(c.begin())>(0, c.begin());
    }
    auto end() {
        return enumerate_iterator<decltype(c.end())>(c.size(), c.end());
    }
};

} // namespace iter

#endif // ENUMERATE_H_INCLUDED_32E3C8F6_6B8B_42FA_874C_7008AA033987
