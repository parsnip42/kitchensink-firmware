#include "macroset.h"

MacroSet::MacroSet()
{
    for (std::size_t i(0); i < mIndex.size(); ++i)
    {
        StrBuf<12> macroName("Macro ");
        
        macroName.appendInt(i);
        
        mIndex[i].type = MacroType::kSync;
        mIndex[i].name = macroName;
    }
}

