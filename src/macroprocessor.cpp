#include "macroprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"

#include <keylayouts.h>

MacroProcessor::MacroProcessor()
{
    mMacroSet.insert(0, {
            KeyEvent(KeyId(KEY_T), false),
            KeyEvent(KeyId(KEY_T)),
            KeyEvent(KeyId(KEY_S), false),
            KeyEvent(KeyId(KEY_S)),
            KeyEvent(KeyId(KEY_E), false),
            KeyEvent(KeyId(KEY_E)),
            KeyEvent(KeyId(KEY_T), false),
            KeyEvent(KeyId(KEY_T)),
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
            eventQueue.pushFront(*it);
        }

        return true;
    }

    return false;
}

