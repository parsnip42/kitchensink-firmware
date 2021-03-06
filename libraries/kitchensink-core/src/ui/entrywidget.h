#ifndef INCLUDED_ENTRYWIDGET_H
#define INCLUDED_ENTRYWIDGET_H

#include "timer/timermanager.h"
#include "event/eventstage.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/action.h"
#include "ui/dimension.h"
#include "ui/widget.h"
#include "ui/virtualkeyboard.h"
#include "ui/widgetcontainer.h"

#include <cstdint>

class Event;
class Timer;

class EntryWidget : public Widget
{
public:
    class Content
    {
    public:
        Content() = default;
        virtual ~Content() = default;

    public:
        virtual bool insertChar(char c, int position) = 0;
        virtual bool eraseChar(int position) = 0;
        virtual StrRef textContent() = 0;
    };
    
public:
    EntryWidget(TimerManager&   timer,
                Content* nContent);

    EntryWidget(EntryWidget&&) = default;

public:
    virtual bool processEvent(const Event& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

private:
    bool processVKeyboard(const Event& event);
    bool processCursor(const Event& event);

public:
    Content* content;

private:
    Timer           mFlashTimer;
    bool            mFocused;
    bool            mFlash;
    std::size_t     mCursorPosition;
    VirtualKeyboard mVKeyboard;

private:
    EntryWidget(const EntryWidget&) = delete;
    EntryWidget& operator=(const EntryWidget&) = delete;
};

#endif
