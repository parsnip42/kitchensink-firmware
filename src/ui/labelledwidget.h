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
                   TWidget&&     nWidget);
    
public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool nFocused) override;
    void render(Surface::RowData& rowData, int row) const;

public:
    LabelWidget label;
    TWidget     widget;
};

template <typename TWidget>
inline
LabelledWidget<TWidget>::LabelledWidget(const StrRef& text,
                                        Justify       justify,
                                        TWidget&&     nWidget)
    : label(text, justify)
    , widget(std::move(nWidget))
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
void LabelledWidget<TWidget>::render(Surface::RowData& rowData, int row) const
{
    label.render(rowData, row);
    widget.render(rowData, row);
}

#endif
