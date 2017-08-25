#ifndef INCLUDED_HSTACKWIDGET_H
#define INCLUDED_HSTACKWIDGET_H

#include "types/range.h"
#include "ui/widget.h"
#include "ui/widgetcontainer.h"

#include <array>
#include <cstdint>

class HStackWidget : public Widget
                   , public WidgetContainer
{
public:
    class Element
    {
    public:
        Element(Widget& nWidget);
        
    public:
        Widget& widget;

    private:
        int yOffset;
        int height;

    private:
        friend class HStackWidget;
    };

public:
    template <std::size_t Size>
    using Items = std::array<Element, Size>;
    
private:
    typedef Element* iterator; 
    
public:
    template <std::size_t Size>
    HStackWidget(Items<Size>& items,
                 bool         linear);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;
    
public:
    Widget& focused() const;

private:
    Range<iterator> mItems;
    bool            mLinear;
    iterator        mFocused;
    int             mContentHeight;
};


inline
HStackWidget::Element::Element(Widget& nWidget)
    : widget(nWidget)
    , yOffset(0)
{ }


template <std::size_t Size>
inline
HStackWidget::HStackWidget(Items<Size>& items,
                           bool         linear)
    : mItems(items.begin(), items.end())
    , mLinear(linear)
    , mFocused(items.begin())
    , mContentHeight(0)
{
    setFocused(true);
}

#endif
