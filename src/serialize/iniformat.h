#ifndef INCLUDED_INIFORMAT_H
#define INCLUDED_INIFORMAT_H

#include "storage/storage.h"
#include "types/strbuf.h"

class StrRef;
class StrOStream;

namespace IniFormat
{
class IStream
{
public:
    explicit IStream(Storage::IStream& is);

public:
    bool nextSection(StrRef& sectionName);
    bool nextProperty(StrRef& key, StrRef& value);

private:
    bool nextLine();
    
private:
    Storage::IStream& mIs;
    StrBuf<240>       mCurrentLine;
    bool              mLineConsumed;
    
private:
    IStream(const IStream&) = delete;
    IStream& operator=(const IStream&) = delete;
};

class OStream
{
public:
    explicit OStream(Storage::OStream& os);

public:
    void writeSection(const StrRef& sectionName);
    void writeProperty(const StrRef& key, const StrRef& value);

private:
    Storage::OStream& mOs;

private:
    OStream(const OStream&) = delete;
    OStream& operator=(const OStream&) = delete;
};

};

#endif /* INCLUDED_INIFORMAT_H */
