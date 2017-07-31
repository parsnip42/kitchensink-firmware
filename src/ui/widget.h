#ifndef INCLUDED_WIDGET_H
#define INCLUDED_WIDGET_H

#include "keyeventstage.h"

class Widget : public KeyEventStage
{
public:
    Widget() = default;
    virtual ~Widget() = default;
    
public:
    virtual void processKeyEvent(const KeyEvent&) override;    
    virtual void setFocused(bool focused) = 0;
};

#endif
