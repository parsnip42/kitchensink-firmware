#include "lockset.h"

#include "types/strbuf.h"
#include "types/strostream.h"

LockSet::LockSet()
{
    for (std::size_t i(0); i < mData.size(); ++i)
    {
        StrOStream ostream(mData[i].name);

        ostream.appendStr("Lock ")
               .appendInt(i);
    }
}
