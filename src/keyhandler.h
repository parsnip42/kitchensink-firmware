#ifndef INCLUDED_KEYHANDLER_H
#define INCLUDED_KEYHANDLER_H

#include "keyid.h"
#include "keystate.h"
#include "kskeyboard.h"
#include "layerstack.h"
#include "modifierset.h"
#include "tapping.h"

class KsKeyboard;

class KeyHandler
{
public:
    class Event
    {
    public:
        Event(KeyId           nKeyId,
              KeyState::Value nState,
              int             nTaps);
        
    public:
        KeyId           keyId;
        KeyState::Value state;
        int             taps;
    };
 
public:
    KeyHandler();

public:
    template<typename Callback>
    inline
    bool poll(KsKeyboard&     keyboard,
              const Callback& callback);

public:
    void assignLayer(const Layer* layer, int index);
    void setLayer(int index, bool enabled);
    bool layerEnabled(int layer) const;
    
private:
    LayerStack  mLayerStack;
    ModifierSet mModifierSet;
    Tapping     mTapping;

private:
    KeyHandler(const KeyHandler&) = delete;
    KeyHandler& operator=(const KeyHandler&) = delete;
};


template<typename Callback>
inline
bool KeyHandler::poll(KsKeyboard&     keyboard,
                      const Callback& callback)
{
    return keyboard.poll([&](const KsKeyboard::Event& event)
    {
        KeyId keyId(mLayerStack.at(event.row, event.column));

        mTapping.processKey(keyId);
        
       
        if (keyId.type() == KeyId::kModifier)
        {
            bool updated(false);
            
            if (event.state == KeyState::kPressed)
            {
                updated = mModifierSet[keyId.value()].pressed();
            }

            if (event.state == KeyState::kReleased)
            {
                updated = mModifierSet[keyId.value()].released();
            }

            if (updated)
            {
                if (keyId.value() >= 10)
                {
                    setLayer(keyId.value() - 10, mModifierSet[keyId.value()].active());
                }
                else
                {
                    callback(Event(keyId, event.state, mTapping.count(keyId)));
                }
            }
        }
        else
        {
            callback(Event(keyId, event.state, mTapping.count(keyId)));
        }
    });
}

#endif
