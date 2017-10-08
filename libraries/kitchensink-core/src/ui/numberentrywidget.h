#ifndef INCLUDED_NUMBERENTRYWIDGET_H
#define INCLUDED_NUMBERENTRYWIDGET_H

#include "ui/entrywidget.h"

class Event;
class Timer;
class StrRef;

class NumberEntryWidget : public Widget
                        , public WidgetContainer
{
public:
    class NumberContent : public EntryWidget::Content
    {
    public:
        NumberContent(int min, int max);
        
        virtual ~NumberContent() = default;
        
    public:
        virtual bool insertChar(char c, int position) override;
        virtual bool eraseChar(int position) override;
        virtual StrRef textContent() override;

    public:
        operator int();
        void operator=(int rhs);

    private:
        int normalize();
        
    private:
        int        mMin;
        int        mMax;
        StrBuf<30> mText;
    };
    
public:
    explicit NumberEntryWidget(int    min,
                               int    max,
                               TimerManager& timer);

    NumberEntryWidget(NumberEntryWidget&& rhs);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    virtual void regionInvalidated(const Rectangle& region) override;
    virtual void parented() override;

public:
    NumberContent value;

private:
    EntryWidget mEntryWidget;
    
private:
    NumberEntryWidget(const NumberEntryWidget&) = delete;
    NumberEntryWidget& operator=(const NumberEntryWidget&) = delete;
};

#endif
