#ifndef INCLUDED_STRBUF_H
#define INCLUDED_STRBUF_H

#include "types/strref.h"

#include <cstdio>
#include <cstdint>
#include <cstring>

namespace Types
{

template <std::size_t Size>
class StrBuf
{
public:
    typedef const char* const_iterator;
    
public:
    constexpr StrBuf();
    StrBuf(const StrRef& strRef);

public:
    void appendChar(char c);
    void appendInt(int n);
    void popEnd();
    
public:
    const_iterator begin() const;
    const_iterator end() const;
    std::size_t size() const;
    bool empty() const;
    
public:
    constexpr operator StrRef() const;

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
    strlcpy(mData, strRef.begin(), sizeof(mData));
}

template <std::size_t Size>
inline
void StrBuf<Size>::appendChar(char c)
{
    auto currentSize(size());

    if (currentSize < Size - 1)
    {
        mData[currentSize] = c;
        mData[currentSize + 1] = '\0';
    }
}

template <std::size_t Size>
inline
void StrBuf<Size>::appendInt(int n)
{
    auto currentSize(size());

    snprintf(&mData[currentSize], Size - currentSize, "%d", n);
}

template <std::size_t Size>
inline
void StrBuf<Size>::popEnd()
{
    if (!empty())
    {
        mData[size() - 1] = '\0';
    }
}

template <std::size_t Size>
inline
typename StrBuf<Size>::const_iterator StrBuf<Size>::begin() const
{
    return mData;
}

template <std::size_t Size>
inline
typename StrBuf<Size>::const_iterator StrBuf<Size>::end() const
{
    return mData + size();
}

template <std::size_t Size>
inline
std::size_t StrBuf<Size>::size() const
{
    return strlen(mData);
}

template <std::size_t Size>
inline
bool StrBuf<Size>::empty() const
{
    return (mData[0] == '\0');
}

template <std::size_t Size>
inline
constexpr StrBuf<Size>::operator StrRef() const
{
    return StrRef(mData);
}

}

#endif
