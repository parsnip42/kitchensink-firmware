#ifndef INCLUDED_ARRAYOBJECTSOURCE_H
#define INCLUDED_ARRAYOBJECTSOURCE_H

#include "types/objectsource.h"

template <typename Type>
class ArrayObjectSource : public ObjectSource<Type>
{
public:
    typedef const Type* const_iterator;
    typedef Type        value_type;

public:
    ArrayObjectSource(const_iterator begin,
                      const_iterator end);

public:
    virtual value_type operator[](std::size_t index) const override;
    virtual std::size_t size() const override;
    
private:
    const_iterator mBegin;
    const_iterator mEnd;
};


template <typename Type>
inline
ArrayObjectSource<Type>::ArrayObjectSource(typename ArrayObjectSource<Type>::const_iterator begin,
                                           typename ArrayObjectSource<Type>::const_iterator end)
    : mBegin(begin)
    , mEnd(end)
{ }

template <typename Type>
inline
typename ArrayObjectSource<Type>::value_type ArrayObjectSource<Type>::operator[](std::size_t index) const
{
    return *(mBegin + index);
}

template <typename Type>
inline
std::size_t ArrayObjectSource<Type>::size() const
{
    return mEnd - mBegin;
}

#endif
