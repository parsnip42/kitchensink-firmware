#ifndef INCLUDED_STRREF_H
#define INCLUDED_STRREF_H

#include <cstdint>
#include <cstring>

namespace Types
{

class StrRef
{
public:
    typedef const char* const_iterator;

    
public:
    constexpr StrRef(const char* str = "");
    
public:
    constexpr const_iterator begin() const;
    const_iterator end() const;
    std::size_t size() const;
    
private:
    const char* mData;
};


inline
constexpr StrRef::StrRef(const char* str)
    : mData(str)
{ }

inline
constexpr StrRef::const_iterator StrRef::begin() const
{
    return mData;
}

inline
StrRef::const_iterator StrRef::end() const
{
    return mData + size();
}

inline
std::size_t StrRef::size() const
{
    return strlen(mData);
}

}

#endif
