#ifndef INCLUDED_KEYSOURCE_H
#define INCLUDED_KEYSOURCE_H

#include "event/eventstage.h"
#include "event/eventsource.h"
#include "layerstack.h"
#include "keylocation.h"
#include "hardware/keyhardware.h"

#include <cstdint>

class KeyLocation;

class KeySource : public EventSource
{
public:
    KeySource(KeyHardware& keyHardware,
              LayerStack&  layerStack);

public:
    virtual void pollEvent(EventStage& next) override;
    virtual bool flushEvents(EventStage& next) override;
    
public:
    void setLayer(int layer, bool enabled);
    int topLayer();

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
