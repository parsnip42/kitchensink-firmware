#ifndef INCLUDED_EVENTSTREAMSCREEN_H
#define INCLUDED_EVENTSTREAMSCREEN_H

#include "event/event.h"
#include "types/circularbuffer.h"
#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/labelwidget.h"
#include "ui/widgetset.h"
#include "ui/screen.h"

class Widget;

class EventStreamScreen : public Screen
{
public:
    EventStreamScreen();

public:
    virtual bool processEvent(const Event& event) override;
    
    virtual Widget& rootWidget() override;
    
private:
    CircularBuffer<Event, 5> mEvents;
    LabelWidget              mLabels[4];
    HStackWidget::Items<4>   mItems;
    HStackWidget             mHStackWidget;
};

#endif










