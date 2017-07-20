#include "macroprocessor.h"

#include "keyevent.h"

void MacroProcessor::processKeyEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMacro)
    {
        auto macroIndex(keyId.value());

        if (macroIndex < mMacroSet.size())
        {
            const auto& macro(mMacroSet[keyId.value()]);
            const auto& content(macro.content());
            
            if (event.pressed)
            {
                for (const auto& event : content)
                {
                    mNext.processKeyEvent(event);
                }
            }
            else if (macro.type == MacroType::kInvert)
            {
                for (auto event : content.reverse())
                {
                    event.pressed = !event.pressed;
                    mNext.processKeyEvent(event);
                }
            }
        }
    }
    else
    {
        mNext.processKeyEvent(event);
    }
}

