#include "types/strinstream.h"

#include "types/stroutstream.h"
#include "types/strutil.h"

#include <algorithm>

StrInStream::StrInStream(InStream& inStream)
    : mInStream(inStream)
{ }

bool StrInStream::readLine(const StrOutStream& os)
{
    os.reset();
    
    std::array<uint8_t, 1> buffer;
    ArrayOutStream         bufferOut(buffer);

    while (mInStream.read(bufferOut, 1) == 1)
    {
        char c(buffer[0]);

        if (c == '\n' || c =='\r')
        {
            return true;
        }
        else
        {
            os.appendChar(c);
            bufferOut.reset();
        }
    }
    
    return !os.str().empty();
}
