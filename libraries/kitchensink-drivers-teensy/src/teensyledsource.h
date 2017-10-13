#ifndef INCLUDED_TEENSYLEDSOURCE_H
#define INCLUDED_TEENSYLEDSOURCE_H

#include "event/eventsource.h"

#include <cstdint>

class EventStage;

class TeensyLedSource : public EventSource
{
public:
    TeensyLedSource();
    
public:
    virtual void pollEvent(EventStage& next) override;

private:
    uint8_t mMaskValue;
};

#endif
