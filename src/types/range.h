#ifndef INCLUDED_RANGE_H
#define INCLUDED_RANGE_H

#include <iterator>

template <typename T>
class Range
{
public:
    constexpr Range() = default;
    
    constexpr Range(const T& begin,
                    const T& end);

public:
    const T& begin() const;
    const T& end() const;

    T& begin();
    T& end();

public:
    Range<std::reverse_iterator<T>> reverse() const;
    
private:
    T mBegin;
    T mEnd;
};


template <typename T>
inline
constexpr Range<T>::Range(const T& begin,
                          const T& end)
    : mBegin(begin)
    , mEnd(end)
{ }

template <typename T>
inline
const T& Range<T>::begin() const
{
    return mBegin;
}

template <typename T>
inline
const T& Range<T>::end() const
{
    return mEnd;
}

template <typename T>
inline
T& Range<T>::begin()
{
    return mBegin;
}

template <typename T>
inline
T& Range<T>::end()
{
    return mEnd;
}

template <typename T>
inline
Range<std::reverse_iterator<T>> Range<T>::reverse() const
{
    return Range<std::reverse_iterator<T>>(
        std::reverse_iterator<T>(mEnd),
        std::reverse_iterator<T>(mBegin));
}

#endif /* INCLUDED_RANGE_H */
