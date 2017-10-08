#ifndef INCLUDED_EVENTENTRYWIDGET_H
#define INCLUDED_EVENTENTRYWIDGET_H

#include "timermanager.h"
#include "ui/widget.h"
#include "ui/action.h"
#include "event/event.h"
#include "types/strbuf.h"

class EventEntryWidget : public Widget
{
public:
    explicit EventEntryWidget(TimerManager& timer);

    EventEntryWidget(EventEntryWidget&&) = default;

public:
    virtual bool processEvent(const Event& inEvent) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    void update();
    
public:
    Event  event;
    Action eventSelected;

private:
    Timer mFlashTimer;
    bool          mFocused;
    bool          mFlash;
    bool          mTrigger;

private:
    EventEntryWidget(const EventEntryWidget&) = delete;
    EventEntryWidget& operator=(const EventEntryWidget&) = delete;
};

#endif

