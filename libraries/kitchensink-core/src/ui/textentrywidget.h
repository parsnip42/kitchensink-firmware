#ifndef INCLUDED_TEXTENTRYWIDGET_H
#define INCLUDED_TEXTENTRYWIDGET_H

#include "ui/entrywidget.h"

class Event;
class Timer;
class StrRef;

class TextEntryWidget : public Widget
                      , public WidgetContainer
{
public:
    class TextContent : public EntryWidget::Content
    {
    public:
        TextContent() = default;
        virtual ~TextContent() = default;
        
    public:
        virtual bool insertChar(char c, int position) override;
        virtual bool eraseChar(int position) override;
        virtual StrRef textContent() override;

    public:
        operator StrRef() const;
        void operator=(const StrRef& rhs);

    private:
        StrBuf<30> mText;
    };
    
public:
    explicit TextEntryWidget(Timer& timer);

    TextEntryWidget(TextEntryWidget&& rhs);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    virtual void regionInvalidated(const Rectangle& region) override;
    virtual void parented() override;

public:
    TextContent text;

private:
    EntryWidget mEntryWidget;
    
private:
    TextEntryWidget(const TextEntryWidget&) = delete;
    TextEntryWidget& operator=(const TextEntryWidget&) = delete;
};

#endif
