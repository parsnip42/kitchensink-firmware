#ifndef INCLUDED_KEYLOCATIONWIDGET_H
#define INCLUDED_KEYLOCATIONWIDGET_H

#include "ui/widget.h"
#include "ui/action.h"
#include "types/strbuf.h"
#include "keylocation.h"
#include "timer.h"

class KeySource;
class Timer;

class KeyLocationWidget : public Widget
{
public:
    KeyLocationWidget(Timer&     timer,
                      KeySource& keySource);

public:
    virtual bool processEvent(const Event& inEvent) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    void clear();
    
public:
    KeyLocation location;
    Action      locationSelected;
    
private:
    KeySource&    mKeySource;
    Timer::Handle mFlashTimer;
    StrBuf<24>    mLocationStr;
    bool          mLocationSet;
    bool          mFocused;
    bool          mFlash;
    bool          mTrigger;
};

#endif
