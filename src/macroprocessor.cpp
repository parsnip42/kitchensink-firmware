#include "macroprocessor.h"

#include "eventqueue.h"
#include "keyevent.h"

#include <keylayouts.h>

MacroProcessor::MacroProcessor()
{
    // mMacroSet.setMacro(0, {
    //         KeyEvent(KeyId(KEY_T), false),
    //         KeyEvent(KeyId(KEY_T)),
    //         KeyEvent(KeyId(KEY_S), false),
    //         KeyEvent(KeyId(KEY_S)),
    //         KeyEvent(KeyId(KEY_E), false),
    //         KeyEvent(KeyId(KEY_E)),
    //         KeyEvent(KeyId(KEY_T), false),
    //         KeyEvent(KeyId(KEY_T)),
    //         });

    
    mMacroSet.setMacro(0, {
            KeyEvent(KeyId(KEY_LEFT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    mMacroSet.setMacro(1, {
            KeyEvent(KeyId(KEY_RIGHT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    mMacroSet.setMacro(2, {
            KeyEvent(KeyId(KEY_9)),
            KeyEvent(KeyId(0xe1)),
            });

    mMacroSet.setMacro(3, {
            KeyEvent(KeyId(KEY_0)),
            KeyEvent(KeyId(0xe1)),
            });

    mMacroSet.setMacro(4, {
            KeyEvent(KeyId(KEY_COMMA)),
            KeyEvent(KeyId(0xe1)),
            });

    mMacroSet.setMacro(5, {
            KeyEvent(KeyId(KEY_PERIOD)),
            KeyEvent(KeyId(0xe1)),
            });

    mMacroSet.setMacro(10, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });

    mMacroSet.setMacro(11, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });    
}

bool MacroProcessor::processEvent(const KeyEvent& event,
                                  EventQueue&     eventQueue)
{
    const auto& keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kMacro)
    {
        auto entry(mMacroSet[keyId.value()]);

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
                
        return true;
    }

    return false;
}

