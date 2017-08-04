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

        auto size(widgetSize());
        
        if (row == size.height - 2)
        {
            RenderUtil::fill(rasterLine, 0xf);
        }
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
    
    mTitle.setParent(this, Rectangle(0, 0, size.width, size.height - 2));
    mSearch.setParent(this, Rectangle(size));
}

StrRef MenuTitleWidget::filter() const
{
    return mSearch.text;
}
