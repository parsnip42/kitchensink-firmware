#ifndef INCLUDED_LEDSOURCE_H
#define INCLUDED_LEDSOURCE_H

#include <cstdint>

class KeyEventStage;

class LedSource
{
public:
    LedSource();
    
public:
    void pollKeyEvent(KeyEventStage& next);
    
private:
    uint8_t mMaskValue;
};

#endif
