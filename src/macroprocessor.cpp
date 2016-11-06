#include "macroprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"

#include <keylayouts.h>

MacroProcessor::MacroProcessor()
{
    mMacroSet.insert(0, {
            KeyId(KEY_T),
            KeyId(KEY_E),
            KeyId(KEY_S),
            KeyId(KEY_T),
            });

}

bool MacroProcessor::processEvent(const KeyEvent& event,
                                  EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMacro
        && event.pressed)
    {
        auto entry(mMacroSet[0]);

        for (auto it(entry.first); it != entry.second; ++it)
        {
            switch (it->action)
            {
            case MacroElement::Action::kTap:
                eventQueue.pushBack(KeyEvent(it->keyId, true));
                eventQueue.pushBack(KeyEvent(it->keyId, false));
                break;
                
            case MacroElement::Action::kPress:
                eventQueue.pushBack(KeyEvent(it->keyId, true));
                break;
                
            case MacroElement::Action::kRelease:
                eventQueue.pushBack(KeyEvent(it->keyId, false));
                break;
            }
        }

        return true;
    }

    return false;
}

