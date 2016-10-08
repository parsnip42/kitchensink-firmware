#ifndef INCLUDED_KEYHANDLER_H
#define INCLUDED_KEYHANDLER_H

#include "keyevent.h"
#include "keyid.h"
#include "keystate.h"
#include "kskeyboard.h"
#include "layerstack.h"
#include "modifierset.h"
#include "tapping.h"

class KeyHandler
{
public:
    explicit KeyHandler(KsKeyboard& keyboard);

public:
    template<typename Callback>
    inline
    void poll(const Callback& callback);
    
public:
    void assignLayer(int index, const Layer& layer);
    void setLayer(int index, bool enabled);
    bool layerEnabled(int layer) const;
    
public:
    KsKeyboard& mKeyboard;
    LayerStack  mLayerStack;
    ModifierSet mModifierSet;
    Tapping     mTapping;
    uint8_t     mModifierMask;
    
private:
    KeyHandler(const KeyHandler&) = delete;
    KeyHandler& operator=(const KeyHandler&) = delete;
};


template<typename Callback>
inline
void KeyHandler::poll(const Callback& callback)
{
    mKeyboard.poll([&](const KsKeyboard::Event& event)
    {
        KeyId keyId(mLayerStack.at(event.row, event.column));

        if (event.state == KeyState::kPressed)
        {
            mTapping.processKey(keyId);
        }
        
        int count(mTapping.count(keyId));
       
        if (keyId.type() == KeyId::kModifier)
        {
            bool updated(false);

            int modifier(keyId.value());
            
            if (event.state == KeyState::kPressed)
            {
                updated = mModifierSet[modifier].pressed();
            }

            if (event.state == KeyState::kReleased)
            {
                updated = mModifierSet[modifier].released();
            }

            if (updated)
            {
                uint8_t active(mModifierSet[modifier].active());
                
                if (modifier >= 10)
                {
                    setLayer(modifier - 10, active);
                }
                else
                {
                    uint8_t set(active << modifier);
                    uint8_t clear(~(1 << modifier));
                    
                    mModifierMask = (mModifierMask & clear) | set;

                    callback(KeyEvent(KeyId::ModifierMask(mModifierMask),
                                      KeyState::kPressed,
                                      0));
                }
            }
        }
        else
        {
            callback(KeyEvent(keyId, event.state, count));
        }
    });
}

#endif
