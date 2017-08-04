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
                   int           nSeparationPct = 50,
                   int           nMargin = 0);
    
public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool nFocused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;
    
public:
    LabelWidget label;
    TWidget     widget;
    int         separationPct;
    int         margin;
    int         labelWidth;
};


template <typename TWidget>
inline
LabelledWidget<TWidget>::LabelledWidget(const StrRef& text,
                                        Justify       justify,
                                        TWidget&&     nWidget,
                                        int           nSeparationPct,
                                        int           nMargin)
    : label(text, justify)
    , widget(std::move(nWidget))
    , separationPct(nSeparationPct)
    , margin(nMargin)
    , labelWidth(0)
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
    
    labelWidth = ((size.width * separationPct) / 100);
    
    label.setParent(this,
                    Rectangle(0,
                              0,
                              labelWidth,
                              size.height));
    
    widget.setParent(this,
                     Rectangle(0,
                               0,
                               size.width - (labelWidth + margin),
                               size.height));
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::render(const RasterLine& rasterLine, int row)
{
    label.render(rasterLine.subset(0, labelWidth), row);
    widget.render(rasterLine.subset(labelWidth + margin), row);
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

#endif


