#ifndef INCLUDED_INSTREAM_H
#define INCLUDED_INSTREAM_H

#include <cstdint>

class OutStream;

class InStream
{
public:
    InStream() = default;
    virtual ~InStream() = default;
    
public:
    virtual std::size_t read(OutStream& os, std::size_t len) = 0;
};

#endif
