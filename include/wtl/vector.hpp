//  :copyright: (c) 2009-2017 LLVM Team.
//  :copyright: (c) 2017 Alex Huszagh.
//  :license: BSD-like or MIT, see LICENSE.md for more details.

#pragma once

#include <vector>


namespace wtl
{
// DECLARATION
// -----------


/** \brief STL vector wrapper.
 *
 *  Binds a pointer and the vector length, accepting either a C++
 *  vector, a null-terminated vector, a character array and length,
 *  or an begin/end pointer pair.
 *
 *  \warning The lifetime of the source data must outlive the wrapper.
 *  The wrapper has **no** ownership, and is merely an STL-like wrapper
 *  for performance reasons.
 */
template <typename T>
class vector
{
protected:
    const T *data_ = nullptr;
    size_t size_ = 0;

    // NON-MEMBER FUNCTIONS
    // --------------------
    template <typename U>
    friend void swap(vector<U> &left,
        vector<U> &right);

    // RELATIONAL OPERATORS
    template <typename U>
    friend bool operator==(const vector<U> &left,
        const vector<U> &right) noexcept;

    template <typename U>
    friend bool operator!=(const vector<U> &left,
        const vector<U> &right) noexcept;

    template <typename U>
    friend bool operator<(const vector<U> &left,
        const vector<U> &right) noexcept;

    template <typename U>
    friend bool operator<=(const vector<U> &left,
        const vector<U> &right) noexcept;

    template <typename U>
    friend bool operator>(const vector<U> &left,
        const vector<U> &right) noexcept;

    template <typename U>
    friend bool operator>=(const vector<U> &left,
        const vector<U> &right) noexcept;

public:
    // MEMBER TYPES
    // ------------
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator<pointer> reverse_iterator;
    typedef std::reverse_iterator<const_pointer> const_reverse_iterator;

    // MEMBER FUNCTIONS
    // ----------------
    vector() = default;
    vector(const vector<T> &vector);
    vector<T> & operator=(const vector<T> &vector);
    vector(vector<T> &&vector);
    vector<T> & operator=(vector<T> &&vector);

    vector(const std::vector<T> &vector);
    vector<T> & operator=(const std::vector<T> &vector);
    vector(const T* t,
        size_type n);

    // ITERATORS
    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // CAPACITY
    size_t size() const;
    bool empty() const noexcept;

    // ELEMENT ACCESS
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    const_pointer data() const noexcept;

    // MODIFIERS
    void swap(vector<T> &other);

    // CONVERSIONS
    explicit operator bool() const;
    explicit operator std::vector<T>() const;
};


// IMPLEMENTATION
// --------------


template <typename T>
void swap(vector<T> &left,
    vector<T> &right)
{
    left.swap(right);
}


template <typename T>
bool operator==(const vector<T> &left,
    const vector<T> &right) noexcept
{
    return left.size() == right.size() && std::equal(left.begin(), left.end(), right.begin());
}


template <typename T>
bool operator!=(const vector<T> &left,
    const vector<T> &right) noexcept
{
    return !(left == right);
}


template <typename T>
bool operator<(const vector<T> &left,
    const vector<T> &right) noexcept
{
    return std::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}


template <typename T>
bool operator<=(const vector<T> &left,
    const vector<T> &right) noexcept
{
    return !(right < left);
}


template <typename T>
bool operator>(const vector<T> &left,
    const vector<T> &right) noexcept
{
    return right < left;
}


template <typename T>
bool operator>=(const vector<T> &left,
    const vector<T> &right) noexcept
{
    return !(left < right);
}


template <typename T>
vector<T>::vector(const vector<T> &vector):
    data_(vector.data()),
    size_(vector.size())
{}


template <typename T>
vector<T> & vector<T>::operator=(const vector<T> &vector)
{
    data_ = vector.data();
    size_ = vector.size();
    return *this;
}


template <typename T>
vector<T>::vector(vector<T> &&vector)
{
    swap(vector);
}


template <typename T>
vector<T> & vector<T>::operator=(vector<T> &&vector)
{
    swap(vector);
    return *this;
}

template <typename T>
vector<T>::vector(const std::vector<T> &vector):
    data_(vector.data()),
    size_(vector.size())
{}


template <typename T>
vector<T> & vector<T>::operator=(const std::vector<T> &vector)
{
    data_ = vector.data();
    size_ = vector.size();
    return *this;
}


template <typename T>
vector<T>::vector(const T* t,
        size_type n):
    data_(t),
    size_(n)
{}


template <typename T>
auto vector<T>::begin() const
    -> const_iterator
{
    return data_;
}


template <typename T>
auto vector<T>::end() const
    -> const_iterator
{
    return data_ + size_;
}


template <typename T>
auto vector<T>::rbegin() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(end());
}


template <typename T>
auto vector<T>::rend() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(begin());
}


template <typename T>
auto vector<T>::cbegin() const
    -> const_iterator
{
    return begin();
}


template <typename T>
auto vector<T>::cend() const
    -> const_iterator
{
    return end();
}


template <typename T>
auto vector<T>::crbegin() const
    -> const_reverse_iterator
{
    return rbegin();
}


template <typename T>
auto vector<T>::crend() const
    -> const_reverse_iterator
{
    return rend();
}


template <typename T>
size_t vector<T>::size() const
{
    return size_;
}


template <typename T>
bool vector<T>::empty() const noexcept
{
    return size_ == 0;
}


template <typename T>
auto vector<T>::operator[](size_type pos)
    -> reference
{
    assert(pos <= size() && "vector index out of bounds");
    return *const_cast<T*>(data_ + pos);
}


template <typename T>
auto vector<T>::operator[](size_type pos) const
    -> const_reference
{
    assert(pos <= size() && "vector index out of bounds");
    return *(data_ + pos);
}


template <typename T>
auto vector<T>::at(size_type pos)
    -> reference
{
    return operator[](pos);
}


template <typename T>
auto vector<T>::at(size_type pos) const
    -> const_reference
{
    return operator[](pos);
}


template <typename T>
auto vector<T>::front()
    -> reference
{
    assert(!empty() && "vector::front(): vector is empty");
    return *const_cast<T*>(data_);
}


template <typename T>
auto vector<T>::front() const
    -> const_reference
{
    assert(!empty() && "vector::front(): vector is empty");
    return *data_;
}


template <typename T>
auto vector<T>::back()
    -> reference
{
    assert(!empty() && "vector::back(): vector is empty");
    return *const_cast<T*>(data_ + size_ - 1);
}


template <typename T>
auto vector<T>::back() const
    -> const_reference
{
    assert(!empty() && "vector::back(): vector is empty");
    return *(data_ + size_ - 1);
}


template <typename T>
auto vector<T>::data() const noexcept
    -> const_pointer
{
    return data_;
}


template <typename T>
void vector<T>::swap(vector<T> &other)
{
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
}


template <typename T>
vector<T>::operator bool() const
{
    return !empty();
}


template <typename T>
vector<T>::operator std::vector<T>() const
{
    return std::vector<T>(begin(), end());
}

}   /* wtl */
