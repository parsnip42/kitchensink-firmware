#ifndef INCLUDED_LEDSOURCE_H
#define INCLUDED_LEDSOURCE_H

#include <cstdint>

class EventStage;

class LedSource
{
public:
    LedSource();
    
public:
    void pollEvent(EventStage& next);
    
private:
    uint8_t mMaskValue;
};

#endif
