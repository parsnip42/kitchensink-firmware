#ifndef INCLUDED_KEYDISPATCHER_H
#define INCLUDED_KEYDISPATCHER_H

#include "keyevent.h"
#include "keyid.h"
#include "kskeyboard.h"
#include "layerstack.h"
#include "tapping.h"

class EventQueue;

class KeyDispatcher
{
public:
    explicit KeyDispatcher(KsKeyboard& keyboard);

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
    KeyDispatcher(const KeyDispatcher&) = delete;
    KeyDispatcher& operator=(const KeyDispatcher&) = delete;
};

#endif
