#include "types/datarefinstream.h"

#include "types/outstream.h"

std::size_t DataRefInStream::read(OutStream& os, std::size_t len)
{
    auto size(std::min(mData.size() - mPosition, len));

    os.write(DataRef(mData.begin() + mPosition,
                     mData.begin() + mPosition + len));

    mPosition += size;

    return size;
}
