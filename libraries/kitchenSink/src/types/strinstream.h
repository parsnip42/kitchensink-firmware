#ifndef INCLUDED_STRINSTREAM_H
#define INCLUDED_STRINSTREAM_H

#include "types/strref.h"
#include "types/instream.h"
#include "types/arrayoutstream.h"

#include <array>

class StrOutStream;

class StrInStream
{
public:
    explicit StrInStream(InStream& inStream);

public:
    virtual bool readLine(const StrOutStream& os);

private:
    InStream& mInStream;
    
private:
    StrInStream(const StrInStream&) = delete;
    StrInStream& operator=(const StrInStream&) = delete;
};

#endif
