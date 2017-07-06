#include "lockset.h"

#include "types/strbuf.h"

LockSet::LockSet()
{
    for (std::size_t i(0); i < mData.size(); ++i)
    {
        StrBuf<12> lockName("Lock ");
        
        lockName.appendInt(i);
        
        mData[i].name = lockName;
    }
}
