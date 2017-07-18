#include "macroset.h"

#include "types/strostream.h"

MacroSet::MacroSet()
{
    for (std::size_t i = 0; i < mMacroData.size(); ++i)
    {
        mMacroData[i] = Macro(&mMacroPool, i);
    }
}
