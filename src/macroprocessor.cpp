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
            auto macro(macroSet[keyId.value()]);
            auto content(macro.content());
            
            if (event.pressed)
            {
                for (auto it(std::reverse_iterator<decltype(content.begin)>(content.end));
                     it != std::reverse_iterator<decltype(content.end)>(content.begin);
                     ++it)
                {
                    eventQueue.pushFront(*it);
                }
            }
            else if (macro.type() == MacroType::kInvert)
            {
                for (auto it(content.begin); it != content.end; ++it)
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

