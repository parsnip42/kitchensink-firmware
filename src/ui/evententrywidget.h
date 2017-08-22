#ifndef INCLUDED_EVENTENTRYWIDGET_H
#define INCLUDED_EVENTENTRYWIDGET_H

#include "timer.h"
#include "ui/widget.h"
#include "event/event.h"
#include "types/strbuf.h"

class EventEntryWidget : public Widget
{
public:
    explicit EventEntryWidget(Timer& timer);

    EventEntryWidget(EventEntryWidget&&) = default;

public:
    virtual void processEvent(const Event& inEvent) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    void update();
    
public:
    Event event;
    
private:
    Timer::Handle mFlashTimer;
    StrBuf<24>    mEventStr;
    bool          mFocused;
    bool          mFlash;

private:
    EventEntryWidget(const EventEntryWidget&) = delete;
    EventEntryWidget& operator=(const EventEntryWidget&) = delete;
};

#endif

