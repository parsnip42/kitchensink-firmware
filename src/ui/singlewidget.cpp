#include "ui/singlewidget.h"

SingleWidget::SingleWidget(Widget& widget)
    : mWidget(&widget)
    , mParented(false)
{ }

void SingleWidget::processEvent(const Event& event)
{
    mWidget->processEvent(event);
}

void SingleWidget::setFocused(bool focused)
{
    mWidget->setFocused(focused);
}

void SingleWidget::render(const RasterLine& rasterLine, int row)
{
    mWidget->render(rasterLine, row);
}

void SingleWidget::parented()
{
    mWidget->setParent(this, Rectangle(widgetSize()));
    mParented = true;
}

void SingleWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

void SingleWidget::setWidget(Widget& widget)
{
    mWidget = &widget;

    if (mParented)
    {
        mWidget->setParent(this, Rectangle(widgetSize()));
    }
}
