#include "macroset.h"

#include "types/strostream.h"

MacroSet::MacroSet()
{
    for (std::size_t i(0); i < mMacroData.size(); ++i)
    {
        mMacroData[i].type = MacroType::kSync;

        StrOStream ostream(mMacroData[i].name);

        ostream.appendStr("Macro ")
               .appendInt(i);
    }
}

