#ifndef INCLUDED_RANGE_H
#define INCLUDED_RANGE_H

template <typename T>
class Range
{
public:
    constexpr Range() = default;
    
    constexpr Range(const T& nBegin,
                    const T& nEnd);
    
public:
    T begin;
    T end;
};


template <typename T>
inline
constexpr Range<T>::Range(const T& nBegin,
                       const T& nEnd)
    : begin(nBegin)
    , end(nEnd)
{ }
    

#endif /* INCLUDED_RANGE_H */
