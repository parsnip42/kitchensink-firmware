#ifndef INCLUDED_KEYSOURCE_H
#define INCLUDED_KEYSOURCE_H

#include "event/eventstage.h"
#include "layerstack.h"
#include "keylocation.h"
#include "hardware/keyhardware.h"

#include <cstdint>

class KeyLocation;

class KeySource
{
public:
    KeySource(KeyHardware& keyHardware,
              LayerStack&  layerStack);

public:
    void setLayer(int layer, bool enabled);
    int topLayer();

    void pollEvent(EventStage& next);

    bool anyPressed();

public:
    bool readKeyLocation(KeyLocation& location);
    
private:
    void processLayerChange(const LayerStack::Mask& currentMask,
                            const LayerStack::Mask& nextMask,
                            EventStage&             next);

private:
    KeyHardware&     mKeyHardware;
    LayerStack&      mLayerStack;
    LayerStack::Mask mLayerMask;
    
private:
    KeySource(const KeySource&) = delete;
    KeySource& operator=(const KeySource&) = delete;
};

#endif
