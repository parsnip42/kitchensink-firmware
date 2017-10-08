#include "ui/textentrywidget.h"

bool TextEntryWidget::TextContent::insertChar(char c, int position)
{
    mText.insert(mText.begin() + position, c);
    
    return true;
}

bool TextEntryWidget::TextContent::eraseChar(int position)
{
    mText.erase(mText.begin() + position - 1);

    return true;
}

StrRef TextEntryWidget::TextContent::textContent()
{
    return mText;
}

TextEntryWidget::TextContent::operator StrRef() const
{
    return mText;
}

void TextEntryWidget::TextContent::operator=(const StrRef& rhs)
{
    mText = rhs;
}


TextEntryWidget::TextEntryWidget(Timer& timer)
    : mEntryWidget(timer, &text)
{ }

TextEntryWidget::TextEntryWidget(TextEntryWidget&& rhs)
    : text(std::move(rhs.text))
    , mEntryWidget(std::move(rhs.mEntryWidget))
{
    mEntryWidget.content = &text;
}

void TextEntryWidget::setFocused(bool focused)
{
    mEntryWidget.setFocused(focused);
}

void TextEntryWidget::render(const RasterLine& rasterLine, int row)
{
    mEntryWidget.render(rasterLine, row);
}

bool TextEntryWidget::processEvent(const Event& event)
{
    return mEntryWidget.processEvent(event);
}

Dimension TextEntryWidget::minimumSize() const
{
    return mEntryWidget.minimumSize();
}

void TextEntryWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

void TextEntryWidget::parented()
{
    mEntryWidget.setParent(this, Rectangle(widgetSize()));
}
