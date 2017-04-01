/*
 *  :author: The Regents of the University of California.
 *  :license: Public Domain
 *
 *  This file has been placed in the public domain.
 *  There are no restrictions on its use.
 */

#pragma once

#include <string>


namespace wtl
{
// DECLARATION
// -----------


/** \brief STL string wrapper.
 *
 *  Binds a pointer and the string length, accepting either a C++
 *  string, a null-terminated string, a character array and length,
 *  or an begin/end pointer pair.
 *
 *  \warning The lifetime of the source data must outlive the wrapper.
 *  The wrapper has **no** ownership, and is merely an STL-like wrapper
 *  for performacne reasons.
 */
template <
    typename Char,
    typename Traits = std::char_traits<Char>
>
class basic_string
{
protected:
    const Char *data_ = nullptr;
    size_t length_ = 0;

    // TODO: need non-member functions...

public:
    // MEMBER TYPES
    // ------------
    typedef Char value_type;
    typedef Traits traits_type;
    typedef Char& reference;
    typedef const Char& const_reference;
    typedef Char* pointer;
    typedef const Char* const_pointer;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator<pointer> reverse_iterator;
    typedef std::reverse_iterator<const_pointer> const_reverse_iterator;

    // MEMBER VARIABLES
    // ----------------
    static const size_t npos = SIZE_MAX;

    // MEMBER FUNCTIONS
    // ----------------
    basic_string() = default;
    basic_string(const basic_string<Char, Traits> &str);
    basic_string<Char, Traits> & operator=(const basic_string<Char, Traits> &str);
    basic_string(basic_string<Char, Traits> &&str);
    basic_string<Char, Traits> & operator=(basic_string<Char, Traits> &&str);

    basic_string(const std::basic_string<Char, Traits> &str);
    basic_string(const Char *str);
    basic_string(const Char *str,
        size_t n);

    // ITERATORS
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // CAPACITY
    size_t size() const;
    size_t length() const;
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

    // MODIFIERS
    basic_string<Char, Traits> & assign(const basic_string<Char, Traits> &str);
    basic_string<Char, Traits> & assign(const basic_string<Char, Traits> &str,
        size_type subpos,
        size_type sublen);
    basic_string<Char, Traits> & assign(const Char *s);
    basic_string<Char, Traits> & assign(const Char *s,
        size_type n);

//    using Base::insert;
//    using Base::erase;
//    using Base::replace;
//    using Base::pop_back;
//    void swap(This &other);
//
//    // STRING OPERATIONS
//    using Base::c_str;
//    using Base::data;
//    using Base::get_allocator;
//    using Base::copy;
//    using Base::find;
//    using Base::rfind;
//    using Base::find_first_of;
//    using Base::find_last_of;
//    using Base::find_first_not_of;
//    using Base::find_last_not_of;
//    using Base::compare;
//    basic_string<Char, Traits, Alloc> substr(size_type pos = 0, size_type len = npos) const;
};


// IMPLEMENTATION
// --------------

template <typename C, typename T>
basic_string<C, T>::basic_string(const basic_string<C, T> &str):
    data_(str.data()),
    length_(str.length())
{}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator=(const basic_string<C, T> &str)
{
    data_ = str.data_;
    length_ = str.length_;
    return *this;
}


template <typename C, typename T>
basic_string<C, T>::basic_string(basic_string<C, T> &&str):
    data_(str.data_),
    length_(str.length_)
{
    std::swap(data_, str.data_);
    std::swap(length_, str.length_);
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator=(basic_string<C, T> &&str)
{
    std::swap(data_, str.data_);
    std::swap(length_, str.length_);
    return *this;
}


template <typename C, typename T>
basic_string<C, T>::basic_string(const std::basic_string<C, T> &str):
    data_(str.data()),
    length_(str.length())
{}


template <typename C, typename T>
basic_string<C, T>::basic_string(const C *str)
{
    data_ = str;
    length_ = traits_type::length(str);
}


template <typename C, typename T>
basic_string<C, T>::basic_string(const C *str,
    size_t n)
{
    data_ = str;
    length_ = n;
}


template <typename C, typename T>
auto basic_string<C, T>::begin()
    -> iterator
{
    return data_;
}


template <typename C, typename T>
auto basic_string<C, T>::begin() const
    -> const_iterator
{
    return data_;
}


template <typename C, typename T>
auto basic_string<C, T>::end()
    -> iterator
{
    return data_ + length_;
}


template <typename C, typename T>
auto basic_string<C, T>::end() const
    -> const_iterator
{
    return data_ + length_;
}


template <typename C, typename T>
auto basic_string<C, T>::rbegin()
    -> reverse_iterator
{
    return reverse_iterator(begin());
}


template <typename C, typename T>
auto basic_string<C, T>::rbegin() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(begin());
}


template <typename C, typename T>
auto basic_string<C, T>::rend()
    -> reverse_iterator
{
    return reverse_iterator(end());
}


template <typename C, typename T>
auto basic_string<C, T>::rend() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(end());
}


template <typename C, typename T>
auto basic_string<C, T>::cbegin() const
    -> const_iterator
{
    return begin();
}


template <typename C, typename T>
auto basic_string<C, T>::cend() const
    -> const_iterator
{
    return end();
}


template <typename C, typename T>
auto basic_string<C, T>::crbegin() const
    -> const_reverse_iterator
{
    return rbegin();
}


template <typename C, typename T>
auto basic_string<C, T>::crend() const
    -> const_reverse_iterator
{
    return rend();
}


template <typename C, typename T>
size_t basic_string<C, T>::size() const
{
    return length_;
}


template <typename C, typename T>
size_t basic_string<C, T>::length() const
{
    return length_;
}


template <typename C, typename T>
bool basic_string<C, T>::empty() const noexcept
{
    return length_ == 0;
}


template <typename C, typename T>
auto basic_string<C, T>::operator[](size_type pos)
    -> reference
{
    assert(pos <= size() && "string index out of bounds");
    return *(data_ + pos);
}


template <typename C, typename T>
auto basic_string<C, T>::operator[](size_type pos) const
    -> const_reference
{
    assert(pos <= size() && "string index out of bounds");
    return *(data_ + pos);
}


template <typename C, typename T>
auto basic_string<C, T>::at(size_type pos)
    -> reference
{
    return operator[](pos);
}


template <typename C, typename T>
auto basic_string<C, T>::at(size_type pos) const
    -> const_reference
{
    return operator[](pos);
}


template <typename C, typename T>
auto basic_string<C, T>::front()
    -> reference
{
    assert(!empty() && "string::front(): string is empty");
    return *data_;
}


template <typename C, typename T>
auto basic_string<C, T>::front() const
    -> const_reference
{
    assert(!empty() && "string::front(): string is empty");
    return *data_;
}


template <typename C, typename T>
auto basic_string<C, T>::back()
    -> reference
{
    assert(!empty() && "string::back(): string is empty");
    return *(data_ + length_ - 1);
}


template <typename C, typename T>
auto basic_string<C, T>::back() const
    -> const_reference
{
    assert(!empty() && "string::back(): string is empty");
    return *(data_ + length_ - 1);
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::assign(const basic_string<C, T> &str)
{
    data_ = str.data();
    length_ = str.length();
    return *this;
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::assign(const basic_string<C, T> &str,
    size_type subpos,
    size_type sublen)
{
    size_type size = str.size();
    if (subpos > size) {
        throw std::out_of_range("basic_string::assign().");
    }
    return assign(str.data() + subpos, std::min(sublen, size - subpos));
}

template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::assign(const C *s)
{
    data_ = s;
    length_ = traits_type::length(s);
    return *this;
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::assign(const C *s,
    size_type n)
{
    data_ = s;
    length_ = n;
    return *this;
}

// TYPES
// -----

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

}   /* wtl */
