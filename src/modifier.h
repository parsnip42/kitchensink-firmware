#ifndef INCLUDED_MODIFIER_H
#define INCLUDED_MODIFIER_H

#include <cstdint>

class Modifier
{
public:
    Modifier();

public:
    bool active() const;

public:
    void hold();
    void release();
    void toggle();
    
private:
    uint8_t mRefCount;
    bool    mToggle;
    bool    mTrigger;
};

#endif
