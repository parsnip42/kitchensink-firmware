#ifndef INCLUDED_LABELLEDWIDGET_H
#define INCLUDED_LABELLEDWIDGET_H

#include "ui/justify.h"
#include "ui/labelwidget.h"

class StrRef;

template <typename TWidget>
class LabelledWidget : public Widget
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
    virtual Dimension getSize() const override;
    virtual void setSize(const Dimension& size) override;
    virtual void render(Surface::RowData& rowData, int row);

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
Dimension LabelledWidget<TWidget>::getSize() const
{
    return Dimension();
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::setSize(const Dimension& size)
{
    labelWidth = ((size.width * separationPct) / 100);
    
    label.setSize(Dimension(labelWidth,
                            size.height));
    
    widget.setSize(Dimension(size.width - (labelWidth + margin),
                             size.height));
}

template <typename TWidget>
inline
void LabelledWidget<TWidget>::render(Surface::RowData& rowData, int row)
{
    auto labelData(rowData.subset(0, labelWidth));
    auto widgetData(rowData.subset(labelWidth + margin));
    
    label.render(labelData, row);
    widget.render(widgetData, row);
}

#endif
