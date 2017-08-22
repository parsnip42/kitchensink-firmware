#ifndef INCLUDED_SCREEN_H
#define INCLUDED_SCREEN_H

#include "event/eventstage.h"
#include "types/strref.h"

class Widget;

class Screen : public EventStage
{
public:
    Screen() = default;
    virtual ~Screen() = default;
    
public:
    virtual void screenInit();
    virtual Widget& rootWidget() = 0;
};


inline
void Screen::screenInit()
{
}

#endif
