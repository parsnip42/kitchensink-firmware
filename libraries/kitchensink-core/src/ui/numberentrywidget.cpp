#include "ui/numberentrywidget.h"

#include "types/stroutstream.h"
#include "types/strutil.h"

NumberEntryWidget::NumberContent::NumberContent(int min, int max)
    : mMin(min)
    , mMax(max)
{ }

bool NumberEntryWidget::NumberContent::insertChar(char c, int position)
{
    if (c >= '0' && c <= '9')
    {
        mText.insert(mText.begin() + position, c);
        
        return true;
    }

    return false;
}

bool NumberEntryWidget::NumberContent::eraseChar(int position)
{
    mText.erase(mText.begin() + position - 1);
    
    return true;
}

StrRef NumberEntryWidget::NumberContent::textContent()
{
    return mText;
}

NumberEntryWidget::NumberContent::operator int()
{
    return normalize();
}

void NumberEntryWidget::NumberContent::operator=(int rhs)
{
    StrOutStream os(mText);

    os.reset();
    os.appendInt(rhs);
}

int NumberEntryWidget::NumberContent::normalize()
{
    int value(mMin);

    StrUtil::parseUInt(mText, value);

    value = std::max(mMin, value);
    value = std::min(mMax, value);
    
    return value;
}


NumberEntryWidget::NumberEntryWidget(int    min,
                                     int    max,
                                     TimerManager& timer)
    : value(min, max)
    , mEntryWidget(timer, &value)
{ }

NumberEntryWidget::NumberEntryWidget(NumberEntryWidget&& rhs)
    : value(std::move(rhs.value))
    , mEntryWidget(std::move(rhs.mEntryWidget))
{
    mEntryWidget.content = &value;
}

void NumberEntryWidget::setFocused(bool focused)
{
    mEntryWidget.setFocused(focused);
}

void NumberEntryWidget::render(const RasterLine& rasterLine, int row)
{
    mEntryWidget.render(rasterLine, row);
}

bool NumberEntryWidget::processEvent(const Event& event)
{
    return mEntryWidget.processEvent(event);
}

Dimension NumberEntryWidget::minimumSize() const
{
    return mEntryWidget.minimumSize();
}

void NumberEntryWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

void NumberEntryWidget::parented()
{
    mEntryWidget.setParent(this, Rectangle(widgetSize()));
}
