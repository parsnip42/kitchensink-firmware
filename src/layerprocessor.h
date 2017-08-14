#ifndef INCLUDED_LAYERPROCESSOR_H
#define INCLUDED_LAYERPROCESSOR_H

#include "event/eventstage.h"

class KeySource;
class Event;

class Event;

class LayerProcessor : public EventStage
{
public:
    explicit LayerProcessor(EventStage& next);

public:
    virtual void processEvent(const Event& event) override;
    
public:
    KeySource* keySource;
    
private:
    EventStage& mNext;
    
private:
    LayerProcessor(const LayerProcessor&) = delete;
    LayerProcessor& operator=(const LayerProcessor&) = delete;
};

#endif
