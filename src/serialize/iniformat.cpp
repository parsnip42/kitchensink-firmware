#include "serialize/iniformat.h"

#include "types/instream.h"
#include "types/outstream.h"
#include "types/strref.h"
#include "types/strutil.h"

namespace IniFormat
{

IStream::IStream(InStream& is)
    : mIs(is)
    , mLineConsumed(true) 
{ }

bool IStream::nextSection(StrRef& sectionName)
{
    while (nextLine())
    {
        StrRef line(mCurrentLine);
        
        line = line.trim();
        
        if (line.beginsWith("[") && line.endsWith("]"))
        {
            sectionName = line.substr(1, line.length() - 2);
            
            return true;
        }
    }

    return false;
}

bool IStream::nextProperty(StrRef& key, StrRef& value)
{
    while (nextLine())
    {
        StrRef line(mCurrentLine);

        line = line.trim();

        if (line.beginsWith("[") && line.endsWith("]"))
        {
            mLineConsumed = false;
            break;
        }
        
        if (!line.beginsWith(";") &&
            StrUtil::cutTrim(line, key, '=', value))
        {
            return true;
        }
    }

    return false;
}

bool IStream::nextLine()
{
    if (!mLineConsumed)
    {
        mLineConsumed = true;
        return true;
    }
        
    return mIs.readLine(mCurrentLine);
}


OStream::OStream(OutStream& os)
    : mOs(os)
{ }

void OStream::writeSection(const StrRef& sectionName)
{
    mOs.write("\n[");
    mOs.write(sectionName);
    mOs.write("]");
    mOs.write("\n");
}

void OStream::writeProperty(const StrRef& key, const StrRef& value)
{
    mOs.write(key);
    mOs.write("=");
    mOs.write(value);
    mOs.write("\n");
}

}
