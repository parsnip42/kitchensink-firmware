#ifndef INCLUDED_INSTREAM_H
#define INCLUDED_INSTREAM_H

class StrOStream;

class InStream
{
public:
    InStream() = default;
    virtual ~InStream() = default;
    
public:
    virtual bool readLine(const StrOStream& os) = 0;
};

#endif
