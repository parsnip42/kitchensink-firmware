#ifndef INCLUDED_KEYSOURCE_H
#define INCLUDED_KEYSOURCE_H

#include "event/eventstage.h"
#include "layerstack.h"
#include "keylocation.h"

#include <cstdint>

class KsKeyboard;
class KeyLocation;

class KeySource
{
public:
    KeySource(KsKeyboard& keyboard,
              LayerStack& nLayerStack);

public:
    void setLayer(int layer, bool enabled);
    int topLayer();

    void pollEvent(EventStage& next);

    bool anyPressed();

public:
    KeyLocation readNextKeyLocation();
    
private:
    void processLayerChange(const LayerStack::Mask& currentMask,
                            const LayerStack::Mask& nextMask,
                            EventStage&             next);

public:
    LayerStack& layerStack;
    
private:
    KsKeyboard&      mKeyboard;
    LayerStack::Mask mLayerMask;
    
private:
    KeySource(const KeySource&) = delete;
    KeySource& operator=(const KeySource&) = delete;
};

#endif
