#include "types/strinstream.h"

#include "types/strostream.h"
#include "types/strutil.h"

StrInStream::StrInStream(const StrRef& str)
    : mStr(str)
    , mToken(StrUtil::nextToken(mStr, "\r\n"))
{ }

bool StrInStream::readLine(const StrOStream& os)
{
    os.reset();
    os.appendStr(mToken);
    
    mToken = StrUtil::nextToken(mStr, "\r\n", mToken);

    return !mToken.empty();
}
