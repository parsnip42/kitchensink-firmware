#ifndef INCLUDED_PASSWORDENTRYWIDGET_H
#define INCLUDED_PASSWORDENTRYWIDGET_H

#include "ui/entrywidget.h"

class Event;
class Timer;
class StrRef;

class PasswordEntryWidget : public Widget
                      , public WidgetContainer
{
public:
    class PasswordContent : public EntryWidget::Content
    {
    public:
        PasswordContent() = default;
        virtual ~PasswordContent() = default;
        
    public:
        virtual bool insertChar(char c, int position) override;
        virtual bool eraseChar(int position) override;
        virtual StrRef textContent() override;

    public:
        operator StrRef() const;
        void operator=(const StrRef& rhs);

    public:
        void updateMask();
        
    private:
        StrBuf<30> mText;
        StrBuf<30> mMask;
    };
    
public:
    explicit PasswordEntryWidget(TimerManager& timer);

    PasswordEntryWidget(PasswordEntryWidget&& rhs);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    virtual void regionInvalidated(const Rectangle& region) override;
    virtual void parented() override;

public:
    PasswordContent password;
    Action          applied;
    
private:
    EntryWidget mEntryWidget;
    
private:
    PasswordEntryWidget(const PasswordEntryWidget&) = delete;
    PasswordEntryWidget& operator=(const PasswordEntryWidget&) = delete;
};

#endif
