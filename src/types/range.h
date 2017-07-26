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
    
    constexpr Range(const std::pair<T, T>& range);

public:
    constexpr const T& begin() const;
    constexpr const T& end() const;

    constexpr T& begin();
    constexpr T& end();

public:
    constexpr Range<std::reverse_iterator<T>> reverse() const;
    
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
constexpr Range<T>::Range(const std::pair<T, T>& range)
    : mBegin(range.first)
    , mEnd(range.second)
{ }

template <typename T>
inline
constexpr const T& Range<T>::begin() const
{
    return mBegin;
}

template <typename T>
inline
constexpr const T& Range<T>::end() const
{
    return mEnd;
}

template <typename T>
inline
constexpr T& Range<T>::begin()
{
    return mBegin;
}

template <typename T>
inline
constexpr T& Range<T>::end()
{
    return mEnd;
}

template <typename T>
inline
constexpr Range<std::reverse_iterator<T>> Range<T>::reverse() const
{
    return Range<std::reverse_iterator<T>>(
        std::reverse_iterator<T>(mEnd),
        std::reverse_iterator<T>(mBegin));
}

#endif /* INCLUDED_RANGE_H */










