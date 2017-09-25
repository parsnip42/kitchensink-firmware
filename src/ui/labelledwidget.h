#ifndef INCLUDED_LABELLEDWIDGET_H
#define INCLUDED_LABELLEDWIDGET_H

#include "ui/justify.h"
#include "ui/labelwidget.h"
#include "ui/rasterline.h"

class StrRef;

template <typename TWidget>
class LabelledWidget : public Widget
                     , public WidgetContainer
{
public:
    LabelledWidget(const StrRef& text,
                   int           nSeparation,
                   TWidget&&     nWidget = TWidget());
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;
    virtual Dimension minimumSize() const;

public:
    LabelWidget label;
    TWidget     widget;
    int         separation;
};


template <typename TWidget>
inline
LabelledWidget<TWidget>::LabelledWidget(const StrRef& text,
                                        int           nSeparation,
                                        TWidget&&     nWidget)
    : label(text, Justify::kLeft, true)
    , widget(std::move(nWidget))
    , separation(nSeparation)
{ }

template <typename TWidget>
inline
bool LabelledWidget<TWidget>::processEvent(const Event& event)
{
    return widget.processEvent(event);
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::setFocused(bool nFocused)
{
    label.setFocused(nFocused);
    widget.setFocused(nFocused);
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::parented()
{
    auto size(widgetSize());
    
    label.setParent(this,
                    Rectangle(0,
                              0,
                              separation,
                              size.height));
    
    widget.setParent(this,
                     Rectangle(0,
                               0,
                               size.width - separation,
                               size.height));
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::render(const RasterLine& rasterLine, int row)
{
    label.render(rasterLine.subset(0, separation), row);
    widget.render(rasterLine.subset(separation), row);
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

template <typename TWidget>
inline
Dimension LabelledWidget<TWidget>::minimumSize() const
{
    auto labelMin(label.minimumSize());
    auto widgetMin(widget.minimumSize());
        
    return Dimension(labelMin.width + widgetMin.width,
                     std::max(labelMin.height, widgetMin.height));
}

#endif


