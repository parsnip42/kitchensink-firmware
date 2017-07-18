#include "macroprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"
#include "macroset.h"

bool MacroProcessor::processEvent(const MacroSet& macroSet,
                                  const KeyEvent& event,
                                  EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMacro)
    {
        auto macroIndex(keyId.value());

        if (macroIndex < macroSet.size())
        {
            const auto& macro(macroSet[keyId.value()]);
            const auto& content(macro.content());
            
            if (event.pressed)
            {
                for (const auto& event : content.reverse())
                {
                    eventQueue.pushFront(event);
                }
            }
            else if (macro.type == MacroType::kInvert)
            {
                for (auto event : content)
                {
                    event.pressed = !event.pressed;
                    eventQueue.pushFront(event);
                }
            }
        }
        
        return true;
    }

    return false;
}

