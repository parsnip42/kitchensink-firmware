#include "macroset.h"

MacroSet::MacroSet()
{
    for (std::size_t i(0); i < mMacroData.size(); ++i)
    {
        StrBuf<12> macroName("Macro ");
        
        macroName.appendInt(i);
        
        mMacroData[i].type = MacroType::kSync;
        mMacroData[i].name = macroName;
    }
}

