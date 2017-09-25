#ifndef INCLUDED_SCREEN_H
#define INCLUDED_SCREEN_H

#include "event/eventstage.h"
#include "types/strref.h"
#include "ui/action.h"

class Widget;

class Screen : public EventStage
{
public:
    Screen() = default;
    virtual ~Screen() = default;
    
public:
    virtual void screenInit();
    virtual void screenExit();
    virtual Widget& rootWidget() = 0;

public:
    Action screenCompleted;
};


inline
void Screen::screenInit()
{
}

inline
void Screen::screenExit()
{
}

#endif
