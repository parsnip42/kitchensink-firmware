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
            auto entry(macroSet[keyId.value()]);

            if (event.pressed)
            {
                for (auto it(entry.begin()); it != entry.end(); ++it)
                {
                    eventQueue.pushFront(*it);
                }
            }
            else if (keyId.macroType() == KeyId::MacroType::kInvert)
            {
                for (auto it(entry.rbegin()); it != entry.rend(); ++it)
                {
                    auto event(*it);
                
                    event.pressed = !event.pressed;
                
                    eventQueue.pushFront(event);
                }
            }
        }
        
        return true;
    }

    return false;
}

