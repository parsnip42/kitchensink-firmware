#ifndef INCLUDED_STRINSTREAM_H
#define INCLUDED_STRINSTREAM_H

#include "types/strref.h"
#include "types/instream.h"

class StrOStream;

class StrInStream : public InStream
{
public:
    explicit StrInStream(const StrRef& str);

public:
    virtual bool readLine(const StrOStream& os);

private:
    StrRef mStr;
    StrRef mToken;

private:
    StrInStream(const StrInStream&) = delete;
    StrInStream& operator=(const StrInStream&) = delete;
};

#endif
