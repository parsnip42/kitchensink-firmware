#include "keyprocessor.h"

#include "keydispatcher.h"

#include <keylayouts.h>

KeyProcessor::KeyProcessor(KeyDispatcher& keyDispatcher)
    : mKeyDispatcher(keyDispatcher)
{
    mProfile.modifierSet[0] = Modifier("Gm0", KeyId::Layer(3));
    mProfile.modifierSet[1] = Modifier("Gm1", KeyId::Layer(4));
    mProfile.modifierSet[2] = Modifier("Gm2", KeyId::Layer(5));
    mProfile.modifierSet[3] = Modifier("KSP", KeyId::Layer(6));
    mProfile.modifierSet[5] = Modifier("LShft", 0xe1);
    mProfile.modifierSet[6] = Modifier("RShft", 0xe5);

    mProfile.macroSet.setMacro(0, {
            KeyEvent(KeyId(KEY_LEFT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(1, {
            KeyEvent(KeyId(KEY_RIGHT_BRACE)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(2, {
            KeyEvent(KeyId(KEY_9)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(3, {
            KeyEvent(KeyId(KEY_0)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(4, {
            KeyEvent(KeyId(KEY_COMMA)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(5, {
            KeyEvent(KeyId(KEY_PERIOD)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(10, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(11, {
            KeyEvent(KeyId(KEY_MINUS)),
            KeyEvent(KeyId(0xe1)),
            });

    mProfile.macroSet.setMacro(15, {
            KeyEvent(KeyId(KEY_COMMA)),
            KeyEvent(KeyId(0xe2)),
            });
    mProfile.macroSet.setMacro(16, {
            KeyEvent(KeyId(KEY_PERIOD)),
            KeyEvent(KeyId(0xe2)),
            });
    mProfile.macroSet.setMacro(17, {
            KeyEvent(KeyId(KEY_L)),
            KeyEvent(KeyId(0xe2)),
            });    
    mProfile.macroSet.setMacro(18, {
            KeyEvent(KeyId(KEY_F5)),
            KeyEvent(KeyId(0xe2)),
            });
    mProfile.macroSet.setMacro(19, {
            KeyEvent(KeyId(KEY_F9)),
            KeyEvent(KeyId(0xe2)),
            });

}

void KeyProcessor::poll()
{
    mKeyDispatcher.poll(mEventQueue);

    if (!mEventQueue.empty())
    {
        auto event(mEventQueue.pop());

        const auto& keyId(event.keyId);

        if (keyId.type() == KeyId::Type::kLayer)
        {
            mKeyDispatcher.setLayer(keyId.value(), event.pressed, mEventQueue);
        }
        else
        {
            mMacroProcessor.processEvent(mProfile.macroSet,
                                         event,
                                         mEventQueue);
            
            mModifierProcessor.processEvent(mProfile.modifierSet,
                                            event,
                                            mEventQueue);
        }

        mEventQueue.pushFront(event);
    }
}

bool KeyProcessor::hasEvent()
{
    return !mEventQueue.empty();
}

KeyEvent KeyProcessor::popEvent()
{
    return mEventQueue.pop();
}
