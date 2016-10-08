#ifndef INCLUDED_KEYHANDLER_H
#define INCLUDED_KEYHANDLER_H

#include "eventqueue.h"
#include "keyevent.h"
#include "keyid.h"
#include "keystate.h"
#include "kskeyboard.h"
#include "layerstack.h"
#include "tapping.h"

class KeyHandler
{
public:
    explicit KeyHandler(KsKeyboard& keyboard);

public:
    void poll(EventQueue& eventQueue);
    void pressLayer(int index, EventQueue& eventQueue);
    void releaseLayer(int index, EventQueue& eventQueue);
        
public:
    void assignLayer(int index, const Layer& layer);
    void setLayer(int index, bool enabled);
    bool layerEnabled(int layer) const;
    
private:
    KsKeyboard& mKeyboard;
    LayerStack  mLayerStack;
    Tapping     mTapping;
    
private:
    KeyHandler(const KeyHandler&) = delete;
    KeyHandler& operator=(const KeyHandler&) = delete;
};

#endif
