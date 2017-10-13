#ifndef INCLUDED_LEDSOURCE_H
#define INCLUDED_LEDSOURCE_H

#include "event/eventsource.h"

#include <cstdint>

class EventStage;

class LedSource : public EventSource
{
public:
    LedSource();
    
public:
    virtual void pollEvent(EventStage& next) override;

private:
    uint8_t mMaskValue;
};

#endif
