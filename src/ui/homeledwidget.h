#ifndef INCLUDED_HOMELEDWIDGET_H
#define INCLUDED_HOMELEDWIDGET_H

#include "timer.h"
#include "ui/widget.h"
#include "ui/action.h"
#include "event/event.h"
#include "types/strbuf.h"

class HomeLedWidget : public Widget
{
public:
    explicit HomeLedWidget(Timer& timer);

    HomeLedWidget(HomeLedWidget&&) = default;

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
    Timer::Handle mFlashTimer;
    StrBuf<24>    mEventStr;
    bool          mFocused;
    bool          mFlash;
    bool          mTrigger;

private:
    HomeLedWidget(const HomeLedWidget&) = delete;
    HomeLedWidget& operator=(const HomeLedWidget&) = delete;
};

#endif
