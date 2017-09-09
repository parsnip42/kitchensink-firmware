#ifndef INCLUDED_INSTREAM_H
#define INCLUDED_INSTREAM_H

class StrOutStream;

class InStream
{
public:
    InStream() = default;
    virtual ~InStream() = default;
    
public:
    virtual bool readLine(const StrOutStream& os) = 0;
};

#endif
