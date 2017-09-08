#ifndef INCLUDED_OUTSTREAM_H
#define INCLUDED_OUTSTREAM_H

class StrRef;

class OutStream
{
public:
    OutStream() = default;
    virtual ~OutStream() = default;
    
public:
    virtual void write(const StrRef& str) = 0;
};

#endif
