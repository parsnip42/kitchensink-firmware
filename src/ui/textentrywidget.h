#ifndef INCLUDED_TEXTENTRYWIDGET_H
#define INCLUDED_TEXTENTRYWIDGET_H

#include "timer.h"
#include "event/eventstage.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/dimension.h"
#include "ui/widget.h"
#include "ui/virtualkeyboard.h"
#include "ui/widgetcontainer.h"

#include <cstdint>

class KeyId;
class Event;
class Timer;

class TextEntryWidget : public Widget
{
public:
    explicit TextEntryWidget(Timer& timer);

    TextEntryWidget(TextEntryWidget&&) = default;
    
public:
    virtual void processEvent(const Event& event) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    StrBuf<30>  text;
    std::size_t cursorPosition;
    bool        focused;
    
private:
    Timer::Handle   mFlashTimer;
    bool            mFlash;
    VirtualKeyboard mVKeyboard;
    
private:
    TextEntryWidget(const TextEntryWidget&) = delete;
    TextEntryWidget& operator=(const TextEntryWidget&) = delete;
};

#endif
