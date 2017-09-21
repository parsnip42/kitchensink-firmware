#include "types/arrayoutstream.h"

#include "types/dataref.h"

#include <algorithm>

void ArrayOutStream::write(const DataRef& data)
{
    auto size(std::min(mCapacity - mPosition, data.size()));
    
    std::copy(data.begin(), data.begin() + size, mData + mPosition);

    mPosition += size;
}
