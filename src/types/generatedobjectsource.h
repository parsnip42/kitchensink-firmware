#ifndef INCLUDED_GENERATEDOBJECTSOURCE_H
#define INCLUDED_GENERATEDOBJECTSOURCE_H

#include "types/objectsource.h"

#include <cstdint>

template <typename Type>
class GeneratedObjectSource : public ObjectSource<Type>
{
public:
    typedef Type value_type;
    typedef value_type (*Func)(std::size_t index);

public:
    GeneratedObjectSource(std::size_t size, const Func& func);

public:
    virtual value_type operator[](std::size_t index) const override;
    virtual std::size_t size() const override;

private:
    std::size_t mSize;
    Func        mFunc;
};


template <typename Type>
inline
GeneratedObjectSource<Type>::GeneratedObjectSource(std::size_t size, const Func& func)
    : mSize(size)
    , mFunc(func)
{ }

template <typename Type>
inline
typename GeneratedObjectSource<Type>::value_type GeneratedObjectSource<Type>::operator[](std::size_t index) const
{
    return mFunc(index);
}

template <typename Type>
inline
std::size_t GeneratedObjectSource<Type>::size() const
{
    return mSize;
}

#endif
