#ifndef INCLUDED_STRBUF_H
#define INCLUDED_STRBUF_H

#include "types/strref.h"

#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <cstring>

template <std::size_t Size>
class StrBuf
{
public:
    typedef const char* const_iterator;
    typedef char*       iterator;

public:
    constexpr StrBuf();
    StrBuf(const StrRef& strRef);

public:
    StrBuf<Size>& insert(iterator it, char c);
    StrBuf<Size>& erase(iterator it);
    void clear();
    
public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    iterator begin();
    iterator end();
    
    constexpr std::size_t length() const;
    constexpr bool empty() const;

    char* data();
    constexpr std::size_t capacity() const;
    
public:
    StrBuf<Size>& operator=(const StrRef& strRef);
    constexpr operator StrRef() const;

    const char& operator[](std::size_t n) const;
    char& operator[](std::size_t n);

private:
    constexpr std::size_t length(const char* data) const;

private:
    char mData[Size];
};


template <std::size_t Size>
inline
constexpr StrBuf<Size>::StrBuf()
    : mData{0}
{ }

template <std::size_t Size>
inline
StrBuf<Size>::StrBuf(const StrRef& strRef)
{
    strlcpy(mData, strRef.begin(), std::min(strRef.size() + 1, sizeof(mData)));
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::insert(iterator it, char c)
{
    auto endIt(end());
    
    std::move_backward(it, endIt + 1, endIt + 2);

    *it = c;

    return *this;
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::erase(iterator it)
{
    std::move(it + 1, end(), it);

    *(end() - 1) = '\0';
    
    return *this;
}

template <std::size_t Size>
inline
void StrBuf<Size>::clear()
{
    mData[0] = '\0';
}

template <std::size_t Size>
inline
constexpr typename StrBuf<Size>::const_iterator StrBuf<Size>::begin() const
{
    return mData;
}

template <std::size_t Size>
inline
constexpr typename StrBuf<Size>::const_iterator StrBuf<Size>::end() const
{
    return mData + length();
}

template <std::size_t Size>
inline
typename StrBuf<Size>::iterator StrBuf<Size>::begin()
{
    return mData;
}

template <std::size_t Size>
inline
typename StrBuf<Size>::iterator StrBuf<Size>::end()
{
    return mData + length();
}

template <std::size_t Size>
inline
constexpr std::size_t StrBuf<Size>::length() const
{
    return length(mData);
}

template <std::size_t Size>
inline
constexpr bool StrBuf<Size>::empty() const
{
    return (mData[0] == '\0');
}

template <std::size_t Size>
inline
char* StrBuf<Size>::data()
{
    return mData;
}

template <std::size_t Size>
inline
constexpr std::size_t StrBuf<Size>::capacity() const
{
    return sizeof(mData);
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::operator=(const StrRef& strRef)
{
    strlcpy(mData, strRef.begin(), std::min(strRef.size() + 1, sizeof(mData)));

    return *this;
}

template <std::size_t Size>
inline
constexpr StrBuf<Size>::operator StrRef() const
{
    return StrRef(mData);
}

template <std::size_t Size>
inline
const char& StrBuf<Size>::operator[](std::size_t n) const
{
    return mData[n];
}

template <std::size_t Size>
inline
char& StrBuf<Size>::operator[](std::size_t n)
{
    return mData[n];
}

template <std::size_t Size>
inline
constexpr std::size_t StrBuf<Size>::length(const char* data) const
{
    return (data[0] == '\0') ? 0 : (1 + length(data + 1));
}

#endif
