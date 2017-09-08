#ifndef INCLUDED_INIFORMAT_H
#define INCLUDED_INIFORMAT_H

#include "storage/storage.h"
#include "types/strbuf.h"

class StrRef;
class StrOStream;
class InStream;
class OutStream;

namespace IniFormat
{
class IStream
{
public:
    explicit IStream(InStream& is);

public:
    bool nextSection(StrRef& sectionName);
    bool nextProperty(StrRef& key, StrRef& value);

private:
    bool nextLine();
    
private:
    InStream&   mIs;
    StrBuf<240> mCurrentLine;
    bool        mLineConsumed;
    
private:
    IStream(const IStream&) = delete;
    IStream& operator=(const IStream&) = delete;
};

class OStream
{
public:
    explicit OStream(OutStream& os);

public:
    void writeSection(const StrRef& sectionName);
    void writeProperty(const StrRef& key, const StrRef& value);

private:
    OutStream& mOs;

private:
    OStream(const OStream&) = delete;
    OStream& operator=(const OStream&) = delete;
};

};

#endif

