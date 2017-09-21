#ifndef INCLUDED_OUTSTREAM_H
#define INCLUDED_OUTSTREAM_H

class DataRef;

class OutStream
{
public:
    OutStream() = default;
    virtual ~OutStream() = default;
    
public:
    virtual void write(const DataRef& data) = 0;
};

#endif
