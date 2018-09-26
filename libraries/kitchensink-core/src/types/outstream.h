#ifndef INCLUDED_OUTSTREAM_H
#define INCLUDED_OUTSTREAM_H

#include <cstdint>

class DataRef;

class OutStream
{
public:
    OutStream() = default;
    virtual ~OutStream() = default;
    
public:
    virtual std::size_t write(const DataRef& data) = 0;
};

#endif
