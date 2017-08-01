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
class EventManager;

class TextEntryWidget : public Widget
{
public:
    TextEntryWidget(Surface&         surface,
                    EventManager&    eventManager,
                    WidgetContainer& parent);

    TextEntryWidget(TextEntryWidget&&) = default;
    
public:
    virtual void setFocused(bool nFocused) override;
    virtual void processKeyEvent(const KeyEvent& event) override;

    virtual Dimension getSize() const override
    {
        return mSize;
    }

    virtual void setSize(const Dimension& size) override
    {
        mSize = size;
    }

    void render(Surface::RowData& rowData, int row);
    
public:
    StrBuf<30>  text;
    std::size_t cursorPosition;
    bool        focused;
    
private:
    Surface&         mSurface;
    EventManager&    mEventManager;
    WidgetContainer& mParent;
    Timer::Handle    mFlashTimer;
    bool             mFlash;
    Dimension        mSize;
    
private:
    TextEntryWidget(const TextEntryWidget&) = delete;
    TextEntryWidget& operator=(const TextEntryWidget&) = delete;
};

#endif
