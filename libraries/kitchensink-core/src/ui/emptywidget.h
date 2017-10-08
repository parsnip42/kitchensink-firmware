#ifndef INCLUDED_EMPTYWIDGET_H
#define INCLUDED_EMPTYWIDGET_H

#include "ui/widget.h"

class EmptyWidget : public Widget
{
public:
    // This thing is completely immutable, has no dependencies on other data,
    // and does literally nothing, so this is legit.
    static EmptyWidget Instance;
    
private:
    EmptyWidget() = default;
    EmptyWidget(EmptyWidget&&) = default;
    
public:
    virtual bool canFocus() const override;
    virtual void render(const RasterLine&, int) override;

private:
    EmptyWidget(const EmptyWidget&) = delete;
    EmptyWidget& operator=(const EmptyWidget&) = delete;
};

inline
bool EmptyWidget::canFocus() const
{
    return false;
}

inline
void EmptyWidget::render(const RasterLine&, int)
{ }

#endif
