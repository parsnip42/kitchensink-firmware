#ifndef INCLUDED_TEXTENTRYWIDGET_H
#define INCLUDED_TEXTENTRYWIDGET_H

#include "keyeventstage.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/rectangle.h"
#include "eventmanager.h"
#include "ui/widget.h"
#include "ui/surface.h"
#include "ui/widgetcontainer.h"

#include <cstdint>

class KeyId;
class KeyEvent;
class EventManager;

class TextEntryWidget : public Widget
{
public:
    TextEntryWidget(Surface&         surface,
                    EventManager&    eventManager,
                    WidgetContainer& widgetContainer);

public:
    virtual void redrawContent(bool focused) override;
    virtual void processKeyEvent(const KeyEvent& event) override;

    void render(Surface::RowData& rowData, int row) const;
    
public:
    Rectangle  region;
    StrBuf<30> text;
    
private:
    Surface&         mSurface;
    EventManager&    mEventManager;
    WidgetContainer& mWidgetContainer;
    Timer::Handle    mFlashTimer;
    std::size_t      mCursorPosition;
    bool             mFlash;
    bool             mFocused;
    
private:
    TextEntryWidget(const TextEntryWidget&) = delete;
    TextEntryWidget& operator=(const TextEntryWidget&) = delete;
};

#endif
