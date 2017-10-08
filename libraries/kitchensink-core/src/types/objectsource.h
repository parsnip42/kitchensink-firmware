#ifndef INCLUDED_OBJECTSOURCE_H
#define INCLUDED_OBJECTSOURCE_H

#include <cstdint>

template <typename Type>
class ObjectSource
{
public:
    typedef Type value_type;

public:
    virtual value_type operator[](std::size_t index) const = 0;
    virtual std::size_t size() const = 0;
};

#endif
