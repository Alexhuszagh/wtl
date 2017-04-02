//  :copyright: (c) 2009-2017 LLVM Team.
//  :copyright: (c) 2017 Alex Huszagh.
//  :license: BSD-like or MIT, see LICENSE.md for more details.

#pragma once

#include <algorithm>
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

    // NON-MEMBER FUNCTIONS
    // --------------------
    template <typename C, typename T>
    friend void swap(basic_string<C, T> &left,
        basic_string<C, T> &right);

    template <typename C, typename T>
    friend std::basic_istream<C, T> & operator>>(std::basic_istream<C, T> &stream,
        basic_string<C, T> &str);

    template <typename C, typename T>
    friend std::basic_ostream<C, T> & operator<<(std::basic_ostream<C, T> &stream,
        basic_string<C, T> &str);

    // RELATIONAL OPERATORS
    template <typename C, typename T>
    friend bool operator==(const basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator==(const std::basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator==(const basic_string<C, T> &left,
        const std::basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator==(const C *left,
        const basic_string<C, T> &right);

    template <typename C, typename T>
    friend bool operator==(const basic_string<C, T> &left,
        const C *right);

    template <typename C, typename T>
    friend bool operator!=(const basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator!=(const std::basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator!=(const basic_string<C, T> &left,
        const std::basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator!=(const C *left,
        const basic_string<C, T> &right);

    template <typename C, typename T>
    friend bool operator!=(const basic_string<C, T> &left,
        const C *right);

    template <typename C, typename T>
    friend bool operator<(const basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator<(const std::basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator<(const basic_string<C, T> &left,
        const std::basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator<(const C *left,
        const basic_string<C, T> &right);

    template <typename C, typename T>
    friend bool operator<(const basic_string<C, T> &left,
        const C *right);

    template <typename C, typename T>
    friend bool operator<=(const basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator<=(const std::basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator<=(const basic_string<C, T> &left,
        const std::basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator<=(const C *left,
        const basic_string<C, T> &right);

    template <typename C, typename T>
    friend bool operator<=(const basic_string<C, T> &left,
        const C *right);

    template <typename C, typename T>
    friend bool operator>(const basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator>(const std::basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator>(const basic_string<C, T> &left,
        const std::basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator>(const C *left,
        const basic_string<C, T> &right);

    template <typename C, typename T>
    friend bool operator>(const basic_string<C, T> &left,
        const C *right);

    template <typename C, typename T>
    friend bool operator>=(const basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator>=(const std::basic_string<C, T> &left,
        const basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator>=(const basic_string<C, T> &left,
        const std::basic_string<C, T> &right) noexcept;

    template <typename C, typename T>
    friend bool operator>=(const C *left,
        const basic_string<C, T> &right);

    template <typename C, typename T>
    friend bool operator>=(const basic_string<C, T> &left,
        const C *right);

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
    basic_string(const basic_string<Char, Traits> &str,
        size_type pos,
        size_type len = npos);
    basic_string(const std::basic_string<Char, Traits> &str,
        size_type pos,
        size_type len = npos);
    basic_string(const Char *str);
    basic_string(const Char *str,
        size_t n);
    basic_string(const Char *begin,
        const Char *end);
    basic_string<Char, Traits> & operator=(const Char *str);

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
    basic_string<Char, Traits> & assign(const std::basic_string<Char, Traits> &str);
    basic_string<Char, Traits> & assign(const basic_string<Char, Traits> &str,
        size_type subpos,
        size_type sublen);
    basic_string<Char, Traits> & assign(const std::basic_string<Char, Traits> &str,
        size_type subpos,
        size_type sublen);
    basic_string<Char, Traits> & assign(const Char *s);
    basic_string<Char, Traits> & assign(const Char *s,
        size_type n);
    void swap(basic_string<Char, Traits> &other);

    // OPERATORS
    basic_string<Char, Traits> & operator++();
    basic_string<Char, Traits> operator++(int);
    basic_string<Char, Traits> & operator--();
    basic_string<Char, Traits> operator--(int);
    basic_string<Char, Traits> & operator+=(const size_t shift);
    basic_string<Char, Traits> operator+(const size_t shift);
    basic_string<Char, Traits> & operator-=(const size_t shift);
    basic_string<Char, Traits> operator-(const size_t shift);

    // STRING OPERATIONS
    const Char* c_str() const noexcept;
    const Char* data() const noexcept;

    // FIND
    size_t find(const basic_string<Char, Traits> &str,
        size_t pos = 0) const noexcept;
    size_t find(const std::string &str,
        size_t pos = 0) const;
    size_t find(const char *array,
        size_t pos = 0) const;
    size_t find(const char *cstring,
        size_t pos,
        size_t length) const;
    size_t find(char c,
        size_t pos = 0) const noexcept;

    // FIND FIRST OF
    size_t find_first_of(const basic_string<Char, Traits> &str,
        size_t pos = 0) const noexcept;
    size_t find_first_of(const std::string &str,
        size_t pos = 0) const;
    size_t find_first_of(const char *array,
        size_t pos = 0) const;
    size_t find_first_of(const char *cstring,
        size_t pos,
        size_t length) const;
    size_t find_first_of(char c,
        size_t pos = 0) const noexcept;

    // FIND FIRST NOT OF
    size_t find_first_not_of(const basic_string<Char, Traits> &str,
        size_t pos = 0) const noexcept;
    size_t find_first_not_of(const std::string &str,
        size_t pos = 0) const;
    size_t find_first_not_of(const char *array,
        size_t pos = 0) const;
    size_t find_first_not_of(const char *cstring,
        size_t pos,
        size_t length) const;
    size_t find_first_not_of(char c,
        size_t pos = 0) const noexcept;

    // RFIND
    size_t rfind(const basic_string<Char, Traits> &str,
        size_t pos = 0) const noexcept;
    size_t rfind(const std::string &str,
        size_t pos = 0) const;
    size_t rfind(const char *array,
        size_t pos = 0) const;
    size_t rfind(const char *cstring,
        size_t pos,
        size_t length) const;
    size_t rfind(char c,
        size_t pos = 0) const noexcept;

    // FIND LAST OF
    size_t find_last_of(const basic_string<Char, Traits> &str,
        size_t pos = 0) const noexcept;
    size_t find_last_of(const std::string &str,
        size_t pos = 0) const;
    size_t find_last_of(const char *array,
        size_t pos = 0) const;
    size_t find_last_of(const char *cstring,
        size_t pos,
        size_t length) const;
    size_t find_last_of(char c,
        size_t pos = 0) const noexcept;

    // FIND LAST NOT OF
    size_t find_last_not_of(const basic_string<Char, Traits> &str,
        size_t pos = 0) const noexcept;
    size_t find_last_not_of(const std::string &str,
        size_t pos = 0) const;
    size_t find_last_not_of(const char *array,
        size_t pos = 0) const;
    size_t find_last_not_of(const char *cstring,
        size_t pos,
        size_t length) const;
    size_t find_last_not_of(char c,
        size_t pos = 0) const noexcept;

    // COMPARE
    int compare(const basic_string<Char, Traits> &str) const noexcept;
    int compare(const std::basic_string<Char, Traits> &str) const noexcept;
    int compare(size_t pos,
        size_type len,
        const basic_string<Char, Traits> &str) const;
    int compare(size_type pos,
        size_type len,
        const std::basic_string<Char, Traits> &str) const;
    int compare(size_type pos,
        size_type len,
        const basic_string<Char, Traits> &str,
        size_type subpos,
        size_type sublen) const;
    int compare(size_type pos,
        size_type len,
        const std::basic_string<Char, Traits> &str,
        size_type subpos,
        size_type sublen) const;
    int compare(const Char *s) const;
    int compare(size_type pos,
        size_type len,
        const Char *s) const;
    int compare(size_type pos,
        size_type len,
        const Char *s,
        size_type n) const;

    basic_string<Char, Traits> substr(size_type pos = 0,
        size_type len = npos) const;

    // CONVERSIONS
    explicit operator bool() const;
    explicit operator std::string() const;
};


namespace detail
{
// DETAIL
// ------


template <typename Char>
const Char * find(const Char *first,
    size_t length,
    const Char *substr,
    const size_t sublen) noexcept
{
    auto *substr_first = substr;
    auto *substr_last = substr_first + sublen;
    for (; length >= sublen; --length, ++first) {
        if (std::equal(substr_first, substr_last, first)) {
            return first;
        }
    }
    return nullptr;
}


template <typename Char>
const Char * find_of(const Char *first,
    size_t length,
    const Char *substr,
    const size_t sublen) noexcept
{
    auto *substr_first = substr;
    auto *substr_last = substr_first + sublen;
    for (; length; --length, ++first) {
        if (std::any_of(substr_first, substr_last, [first](Char c) {
            return *first == c;
        })) {
            return first;
        }
    }
    return nullptr;
}


template <typename Char>
const Char * find_not_of(const Char *first,
    size_t length,
    const Char *substr,
    const size_t sublen)
{
    auto *substr_first = substr;
    auto *substr_last = substr_first + sublen;
    for (; length; --length, ++first) {
        if (std::none_of(substr_first, substr_last, [first](Char c) {
            return *first == c;
        })) {
            return first;
        }
    }
    return nullptr;
}


template <typename Char>
const Char * rfind(const Char *last,
    size_t length,
    const Char *substr,
    const size_t sublen)
{
    auto *substr_first = substr;
    auto *substr_last = substr_first + sublen;
    last -= sublen;
    for (; length >= sublen; --length) {
        if (std::equal(substr_first, substr_last, --last)) {
            return last;
        }
    }

    return nullptr;
}


template <typename Char>
const Char * rfind_of(const Char *last,
    size_t length,
    const Char *substr,
    const size_t sublen)
{
    auto *substr_first = substr;
    auto *substr_last = substr_first + sublen;
    for (; length; --length) {
        --last;
        if (std::any_of(substr_first, substr_last, [last](Char c) {
            return *last == c;
        })) {
            return last;
        }
    }
    return nullptr;
}


template <typename Char>
const Char * rfind_not_of(const Char *last,
    size_t length,
    const Char *substr,
    const size_t sublen)
{
    auto *substr_first = substr;
    auto *substr_last = substr_first + sublen;
    for (; length; --length) {
        --last;
        if (std::none_of(substr_first, substr_last, [last](Char c) {
            return *last == c;
        })) {
            return last;
        }
    }
    return nullptr;
}

}   /* detail */


// IMPLEMENTATION
// --------------

template <typename C, typename T>
const size_t basic_string<C, T>::npos;

template <typename C, typename T>
void swap(basic_string<C, T> &left,
    basic_string<C, T> &right)
{
    left.swap(right);
}


template <typename C, typename T>
std::basic_istream<C, T> & operator>>(std::basic_istream<C, T> &stream,
    basic_string<C, T> &str)
{
    // TODO: maybe have to const_cast?
    return stream.read(str.data_, str.length_);
}


template <typename C, typename T>
std::basic_ostream<C, T> & operator<<(std::basic_ostream<C, T> &stream,
    basic_string<C, T> &str)
{
    return stream.write(str.data(), str.length());
}


template <typename C, typename T>
bool operator==(const basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    size_t left_size = left.size();
    return left_size == right.size() && T::compare(left.data(), right.data(), left_size) == 0;
}


template <typename C, typename T>
bool operator==(const std::basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return basic_string<C, T>(left) == right;
}


template <typename C, typename T>
bool operator==(const basic_string<C, T> &left,
    const std::basic_string<C, T> &right) noexcept
{
    return left == basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator==(const C *left,
    const basic_string<C, T> &right)
{
    return basic_string<C, T>(left) == right;
}


template <typename C, typename T>
bool operator==(const basic_string<C, T> &left,
    const C *right)
{
    return left == basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator!=(const basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{

    return !(left == right);
}


template <typename C, typename T>
bool operator!=(const std::basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return !(left == right);
}


template <typename C, typename T>
bool operator!=(const basic_string<C, T> &left,
    const std::basic_string<C, T> &right) noexcept
{
    return !(left == right);
}


template <typename C, typename T>
bool operator!=(const C *left,
    const basic_string<C, T> &right)
{
    return !(left == right);
}


template <typename C, typename T>
bool operator!=(const basic_string<C, T> &left,
    const C *right)
{
    return !(left == right);
}


template <typename C, typename T>
bool operator<(const basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return left.compare(right) < 0;
}


template <typename C, typename T>
bool operator<(const std::basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return basic_string<C, T>(left) < right;
}


template <typename C, typename T>
bool operator<(const basic_string<C, T> &left,
    const std::basic_string<C, T> &right) noexcept
{
    return left < basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator<(const C *left,
    const basic_string<C, T> &right)
{
    return basic_string<C, T>(left) < right;
}


template <typename C, typename T>
bool operator<(const basic_string<C, T> &left,
    const C *right)
{
    return left < basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator<=(const basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return !(right < left);
}


template <typename C, typename T>
bool operator<=(const std::basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return basic_string<C, T>(left) <= right;
}


template <typename C, typename T>
bool operator<=(const basic_string<C, T> &left,
    const std::basic_string<C, T> &right) noexcept
{
    return left <= basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator<=(const C *left,
    const basic_string<C, T> &right)
{
    return basic_string<C, T>(left) <= right;
}


template <typename C, typename T>
bool operator<=(const basic_string<C, T> &left,
    const C *right)
{
    return left <= basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator>(const basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return right < left;
}


template <typename C, typename T>
bool operator>(const std::basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return basic_string<C, T>(left) > right;
}


template <typename C, typename T>
bool operator>(const basic_string<C, T> &left,
    const std::basic_string<C, T> &right) noexcept
{
    return left > basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator>(const C *left,
    const basic_string<C, T> &right)
{
    return basic_string<C, T>(left) > right;
}


template <typename C, typename T>
bool operator>(const basic_string<C, T> &left,
    const C *right)
{
    return left > basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator>=(const basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return !(left < right);
}


template <typename C, typename T>
bool operator>=(const std::basic_string<C, T> &left,
    const basic_string<C, T> &right) noexcept
{
    return basic_string<C, T>(left) >= right;
}


template <typename C, typename T>
bool operator>=(const basic_string<C, T> &left,
    const std::basic_string<C, T> &right) noexcept
{
    return left >= basic_string<C, T>(right);
}


template <typename C, typename T>
bool operator>=(const C *left,
    const basic_string<C, T> &right)
{
    return basic_string<C, T>(left) >= right;
}


template <typename C, typename T>
bool operator>=(const basic_string<C, T> &left,
    const C *right)
{
    return left >= basic_string<C, T>(right);
}


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
    swap(str);
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator=(basic_string<C, T> &&str)
{
    swap(str);
    return *this;
}


template <typename C, typename T>
basic_string<C, T>::basic_string(const std::basic_string<C, T> &str):
    data_(str.data()),
    length_(str.length())
{}


template <typename C, typename T>
basic_string<C, T>::basic_string(const basic_string<C, T> &str,
    size_type pos,
    size_type len)
{
    size_type size_ = str.size();
    if (pos > size_) {
        throw std::out_of_range("basic_string::basic_string().");
    }
    data_ = str + pos;
    length_ = std::min(len, size_ - pos);
}


template <typename C, typename T>
basic_string<C, T>::basic_string(const std::basic_string<C, T> &str,
    size_type pos,
    size_type len)
{
    size_type size_ = str.size();
    if (pos > size_) {
        throw std::out_of_range("basic_string::basic_string().");
    }
    data_ = str + pos;
    length_ = std::min(len, size_ - pos);
}


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
basic_string<C, T>::basic_string(const C *begin,
        const C *end):
    data_(begin),
    length_(end - begin)
{}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator=(const C *str)
{
    assign(str);
    return *this;
}


template <typename C, typename T>
auto basic_string<C, T>::begin() const
    -> const_iterator
{
    return data_;
}


template <typename C, typename T>
auto basic_string<C, T>::end() const
    -> const_iterator
{
    return data_ + length_;
}


template <typename C, typename T>
auto basic_string<C, T>::rbegin() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(end());
}


template <typename C, typename T>
auto basic_string<C, T>::rend() const
    -> const_reverse_iterator
{
    return const_reverse_iterator(begin());
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
    return *const_cast<char*>(data_ + pos);
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
    return *const_cast<char*>(data_);
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
    return *const_cast<char*>(data_ + length_ - 1);
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
basic_string<C, T> & basic_string<C, T>::assign(const std::basic_string<C, T> &str)
{
    return assign(basic_string<C, T>(str));
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
basic_string<C, T> & basic_string<C, T>::assign(const std::basic_string<C, T> &str,
    size_type subpos,
    size_type sublen)
{
    return assign(basic_string<C, T>(str), subpos, sublen);
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::assign(const C *s)
{
    data_ = s;
    length_ = s ? traits_type::length(s) : 0;
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


template <typename C, typename T>
void basic_string<C, T>::swap(basic_string<C, T> &other)
{
    std::swap(data_, other.data_);
    std::swap(length_, other.length_);
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator++()
{
    if (length_) {
        ++data_;
        --length_;
    }
    if (empty()) {
        data_ = nullptr;
    }

    return *this;
}


template <typename C, typename T>
basic_string<C, T> basic_string<C, T>::operator++(int)
{
    basic_string<C, T> copy(*this);
    operator++();

    return copy;
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator--()
{
    if (!empty()) {
        --data_;
        ++length_;
    }
    return *this;
}


template <typename C, typename T>
basic_string<C, T> basic_string<C, T>::operator--(int)
{
    basic_string<C, T> copy(*this);
    operator--();

    return copy;
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator+=(const size_t shift)
{
    const size_t offset = std::min<size_t>(shift, length_);
    data_ += offset;
    length_ -= offset;

    return *this;
}


template <typename C, typename T>
basic_string<C, T> basic_string<C, T>::operator+(const size_t shift)
{
    basic_string<C, T> copy(*this);
    copy += shift;
    return copy;
}


template <typename C, typename T>
basic_string<C, T> & basic_string<C, T>::operator-=(const size_t shift)
{
    if (!empty()) {
        data_ -= shift;
        length_ += shift;
    }
    return *this;
}


template <typename C, typename T>
basic_string<C, T> basic_string<C, T>::operator-(const size_t shift)
{
    basic_string<C, T> copy(*this);
    copy -= shift;
    return copy;
}


template <typename C, typename T>
const C* basic_string<C, T>::c_str() const noexcept
{
    return data_;
}


template <typename C, typename T>
const C* basic_string<C, T>::data() const noexcept
{
    return data_;
}


template <typename C, typename T>
size_t basic_string<C, T>::find(const basic_string<C, T> &str,
    size_t pos) const noexcept
{
    auto *found = detail::find(data()+pos, size()-pos, str.data(), str.size());
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find(const std::string &str,
    size_t pos) const
{
    const char *first = str.data();
    const size_t length = str.size();
    auto *found = detail::find(data()+pos, size()-pos, first, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find(const char *array,
    size_t pos) const
{
    const char *first = array;
    const size_t length = strlen(array);
    auto *found = detail::find(data()+pos, size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find(const char *array,
    size_t pos,
    size_t length) const
{
    auto *found = detail::find(data()+pos, size()-pos, array, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find(char c,
    size_t pos) const noexcept
{
    auto *found = detail::find(data()+pos, size()-pos, &c, 1);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_of(const basic_string<C, T> &str,
    size_t pos) const noexcept
{
    auto *found = detail::find_of(data()+pos, size()-pos, str.data(), str.size());

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_of(const std::string &str,
    size_t pos) const
{
    const char *first = str.data();
    const size_t length = str.size();
    auto *found = detail::find_of(data()+pos, size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_of(const char *array,
    size_t pos) const
{
    const char *first = array;
    const size_t length = strlen(array);
    auto *found = detail::find_of(data()+pos, size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_of(const char *array,
    size_t pos,
    size_t length) const
{
    auto *found = detail::find_of(data()+pos, size()-pos, array, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_of(char c,
    size_t pos) const noexcept
{
    auto *found = detail::find_of(data()+pos, size()-pos, &c, 1);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_not_of(const basic_string<C, T> &str,
    size_t pos) const noexcept
{
    auto *found = detail::find_not_of(data()+pos, size()-pos, str.data(), str.size());

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_not_of(const std::string &str,
    size_t pos) const
{
    const char *first = str.data();
    const size_t length = str.size();
    auto *found = detail::find_not_of(data()+pos, size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_not_of(const char *array,
    size_t pos) const
{
    const char *first = array;
    const size_t length = strlen(array);
    auto *found = detail::find_not_of(data()+pos, size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_not_of(const char *array,
    size_t pos,
    size_t length) const
{
    auto *found = detail::find_not_of(data()+pos, size()-pos, array, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_first_not_of(char c,
    size_t pos) const noexcept
{
    auto *found = detail::find_not_of(data()+pos, size()-pos, &c, 1);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::rfind(const basic_string<C, T> &str,
    size_t pos) const noexcept
{
    auto *found = detail::rfind(end(), size()-pos, str.data(), str.size());
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::rfind(const std::string &str,
    size_t pos) const
{
    const char *first = str.data();
    const size_t length = str.size();
    auto *found = detail::rfind(end(), size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::rfind(const char *array,
    size_t pos) const
{
    const char *first = array;
    const size_t length = strlen(array);
    auto *found = detail::rfind(end(), size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::rfind(const char *array,
    size_t pos,
    size_t length) const
{
    auto *found = detail::rfind(end(), size()-pos, array, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::rfind(char c,
    size_t pos) const noexcept
{
    auto *found = detail::rfind(end(), size()-pos, &c, 1);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_of(const basic_string<C, T> &str,
    size_t pos) const noexcept
{
    auto *found = detail::rfind_of(end(), size()-pos, str.data(), str.size());
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_of(const std::string &str,
    size_t pos) const
{
    const char *first = str.data();
    const size_t length = str.size();
    auto *found = detail::rfind_of(end(), size()-pos, first, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_of(const char *array,
    size_t pos) const
{
    const char *first = array;
    const size_t length = strlen(array);
    auto *found = detail::rfind_of(end(), size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_of(const char *array,
    size_t pos,
    size_t length) const
{
    auto *found = detail::rfind_of(end(), size()-pos, array, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_of(char c,
    size_t pos) const noexcept
{
    auto *found = detail::rfind_of(end(), size()-pos, &c, 1);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_not_of(const basic_string<C, T> &str,
    size_t pos) const noexcept
{
    auto *found = detail::rfind_not_of(end(), size()-pos, str.data(), str.size());

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_not_of(const std::string &str,
    size_t pos) const
{
    const char *first = str.data();
    const size_t length = str.size();
    auto *found = detail::rfind_not_of(end(), size()-pos, first, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_not_of(const char *array,
    size_t pos) const
{
    const char *first = array;
    const size_t length = strlen(array);
    auto *found = detail::rfind_not_of(end(), size()-pos, first, length);

    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_not_of(const char *array,
    size_t pos,
    size_t length) const
{
    auto *found = detail::rfind_not_of(end(), size()-pos, array, length);
    return found ? found - data() : npos;
}


template <typename C, typename T>
size_t basic_string<C, T>::find_last_not_of(char c,
    size_t pos) const noexcept
{
    auto *found = detail::rfind_not_of(end(), size()-pos, &c, 1);
    return found ? found - data() : npos;
}


template <typename C, typename T>
int basic_string<C, T>::compare(const basic_string<C, T> &str) const noexcept
{
    size_t left_size = size();
    size_t right_size = str.size();
    int result = traits_type::compare(data(), str.data(), std::min(left_size, right_size));
    if (result != 0) {
        return result;
    } else if (left_size < right_size) {
        return -1;
    } else if (left_size > right_size) {
        return 1;
    }
    return 0;
}


template <typename C, typename T>
int basic_string<C, T>::compare(const std::basic_string<C, T> &str) const noexcept
{
    return compare(basic_string<C, T>(str));
}


template <typename C, typename T>
int basic_string<C, T>::compare(size_type pos,
    size_type len,
    const basic_string<C, T> &str) const
{
    return basic_string<C, T>(*this, pos, len).compare(str);
}


template <typename C, typename T>
int basic_string<C, T>::compare(size_type pos,
    size_type len,
    const std::basic_string<C, T> &str) const
{
    return basic_string<C, T>(*this, pos, len).compare(str);
}


template <typename C, typename T>
int basic_string<C, T>::compare(size_type pos,
    size_type len,
    const basic_string<C, T> &str,
    size_type subpos,
    size_type sublen) const
{
    return basic_string<C, T>(*this, pos, len).compare(basic_string<C, T>(str, subpos, sublen));
}


template <typename C, typename T>
int basic_string<C, T>::compare(size_type pos,
    size_type len,
    const std::basic_string<C, T> &str,
    size_type subpos,
    size_type sublen) const
{
    return basic_string<C, T>(*this, pos, len).compare(basic_string<C, T>(str, subpos, sublen));
}


template <typename C, typename T>
int basic_string<C, T>::compare(const C *s) const
{
    return compare(basic_string<C, T>(s));
}


template <typename C, typename T>
int basic_string<C, T>::compare(size_type pos,
    size_type len,
    const C *s) const
{
    return basic_string<C, T>(*this, pos, len).compare(s);
}


template <typename C, typename T>
int basic_string<C, T>::compare(size_type pos,
    size_type len,
    const C *s,
    size_type n) const
{
    return basic_string<C, T>(*this, pos, len).compare(s, n);
}


template <typename C, typename T>
basic_string<C, T> basic_string<C, T>::substr(size_type pos,
    size_type len) const
{
    return basic_string<C, T>(*this, pos, len);
}


template <typename C, typename T>
basic_string<C, T>::operator bool() const
{
    return !empty();
}


template <typename C, typename T>
basic_string<C, T>::operator std::string() const
{
    return std::string(data_, length_);
}

// TYPES
// -----

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

}   /* wtl */
