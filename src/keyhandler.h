#ifndef INCLUDED_KEYHANDLER_H
#define INCLUDED_KEYHANDLER_H

#include "keyevent.h"
#include "keyid.h"
#include "kskeyboard.h"
#include "layerstack.h"
#include "tapping.h"

class EventQueue;

class KeyHandler
{
public:
    explicit KeyHandler(KsKeyboard& keyboard);

public:
    void poll(EventQueue& eventQueue);
        
public:
    void assignLayer(int index, const Layer& layer);
    void setLayer(int index, bool enabled, EventQueue& eventQueue);
    
private:
    void pressLayer(int index, EventQueue& eventQueue);
    void releaseLayer(int index, EventQueue& eventQueue);

private:
    KsKeyboard& mKeyboard;
    LayerStack  mLayerStack;
    
private:
    KeyHandler(const KeyHandler&) = delete;
    KeyHandler& operator=(const KeyHandler&) = delete;
};

#endif
