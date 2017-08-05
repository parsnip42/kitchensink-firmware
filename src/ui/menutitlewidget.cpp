#include "ui/menutitlewidget.h"

#include "ui/menuitemwidget.h"
#include "ui/renderutil.h"

MenuTitleWidget::MenuTitleWidget(const StrRef& title,
                                 EventManager& eventManager)
    : mTitle(title)
    , mSearch(eventManager)
{ }

void MenuTitleWidget::processKeyEvent(const KeyEvent& event)
{
    mSearch.processKeyEvent(event);
}

void MenuTitleWidget::setFocused(bool focused)
{
    mSearch.setFocused(focused);
}

void MenuTitleWidget::render(const RasterLine& rasterLine, int row)
{
    if (mSearch.text.empty())
    {
        mTitle.render(rasterLine, row);
    }
    else
    {
        mSearch.render(rasterLine, row);
    }
}
void MenuTitleWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

void MenuTitleWidget::parented()
{
    auto size(widgetSize());
    
    mTitle.setParent(this, Rectangle(size));
    mSearch.setParent(this, Rectangle(size));
}

StrRef MenuTitleWidget::filter() const
{
    return mSearch.text;
}
