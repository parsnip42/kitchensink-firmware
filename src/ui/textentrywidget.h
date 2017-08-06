#ifndef INCLUDED_TEXTENTRYWIDGET_H
#define INCLUDED_TEXTENTRYWIDGET_H

#include "keyeventstage.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/dimension.h"
#include "eventmanager.h"
#include "ui/widget.h"
#include "ui/surface.h"
#include "ui/widgetcontainer.h"

#include <cstdint>

class KeyId;
class KeyEvent;
class Timer;

class TextEntryWidget : public Widget
{
public:
    static constexpr int kPreferredHeight = Font::kHeight + 4;

public:
    explicit TextEntryWidget(Timer& timer);

    TextEntryWidget(TextEntryWidget&&) = default;
    
public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    
public:
    StrBuf<30>  text;
    std::size_t cursorPosition;
    bool        focused;
    
private:
    Timer::Handle mFlashTimer;
    bool          mFlash;
    
private:
    TextEntryWidget(const TextEntryWidget&) = delete;
    TextEntryWidget& operator=(const TextEntryWidget&) = delete;
};

#endif
