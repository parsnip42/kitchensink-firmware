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

    template<typename Callback>
    inline
    void releaseAll(const Callback& callback);
    
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
            KeyState updated(KeyState::kNone);

            int modifier(keyId.value());
            
            if (event.state == KeyState::kPressed)
            {
                updated = mModifierSet[modifier].pressed();
            }

            if (event.state == KeyState::kReleased && count != 2)
            {
                updated = mModifierSet[modifier].released();
            }

            if (updated != KeyState::kNone)
            {
                uint8_t active(updated == KeyState::kPressed);
                
                if (modifier >= 10)
                {
                    releaseAll(callback);
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

template<typename Callback>
inline
void KeyHandler::releaseAll(const Callback& callback)
{
    mKeyboard.pressed([&](const KsKeyboard::Event& event)
    {
        KeyId keyId(mLayerStack.at(event.row, event.column));

        callback(KeyEvent(keyId, KeyState::kReleased, 0));
    });
}

#endif
