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
                   Justify       justify,
                   TWidget&&     nWidget,
                   int           nSeparation);
    
public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;
    virtual Dimension minimumSize() const;

public:
    LabelWidget label;
    TWidget     widget;
    int         separation;
    int         margin;
};


template <typename TWidget>
inline
LabelledWidget<TWidget>::LabelledWidget(const StrRef& text,
                                        Justify       justify,
                                        TWidget&&     nWidget,
                                        int           nSeparation)
    : label(text, justify)
    , widget(std::move(nWidget))
    , separation(nSeparation)
    , margin(justify == Justify::kRight ? 1 : 0)
{ }

template <typename TWidget>
inline
void LabelledWidget<TWidget>::processKeyEvent(const KeyEvent& event)
{
    widget.processKeyEvent(event);
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
                               size.width - (separation + margin),
                               size.height));
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::render(const RasterLine& rasterLine, int row)
{
    label.render(rasterLine.subset(0, separation), row);
    widget.render(rasterLine.subset(separation + margin), row);
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
        
    return Dimension(labelMin.width + margin + widgetMin.width,
                     std::max(labelMin.height, widgetMin.height));
}

#endif


