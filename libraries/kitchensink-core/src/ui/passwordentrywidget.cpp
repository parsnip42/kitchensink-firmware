#include "ui/passwordentrywidget.h"

#include "types/stroutstream.h"

bool PasswordEntryWidget::PasswordContent::insertChar(char c, int position)
{
    mText.insert(mText.begin() + position, c);
    updateMask();
    
    return true;
}

bool PasswordEntryWidget::PasswordContent::eraseChar(int position)
{
    mText.erase(mText.begin() + position - 1);
    updateMask();
    
    return true;
}

StrRef PasswordEntryWidget::PasswordContent::textContent()
{
    return mMask;
}

PasswordEntryWidget::PasswordContent::operator StrRef() const
{
    return mText;
}

void PasswordEntryWidget::PasswordContent::operator=(const StrRef& rhs)
{
    mText = rhs;
}

void PasswordEntryWidget::PasswordContent::updateMask()
{
    if (mMask.length() != mText.length())
    {
        StrOutStream os(mMask);
        
        os.reset();
        
        for (std::size_t i(0); i < mText.length(); ++i)
        {
            os.appendChar('*');
        }
    }
}


PasswordEntryWidget::PasswordEntryWidget(TimerManager& timer)
    : mEntryWidget(timer, &password)
{
    mEntryWidget.applied = Action::action(applied);
}

PasswordEntryWidget::PasswordEntryWidget(PasswordEntryWidget&& rhs)
    : password(std::move(rhs.password))
    , mEntryWidget(std::move(rhs.mEntryWidget))
{
    mEntryWidget.content = &password;
    mEntryWidget.applied = Action::action(applied);
}

void PasswordEntryWidget::setFocused(bool focused)
{
    mEntryWidget.setFocused(focused);
}

void PasswordEntryWidget::render(const RasterLine& rasterLine, int row)
{
    mEntryWidget.render(rasterLine, row);
}

bool PasswordEntryWidget::processEvent(const Event& event)
{
    password.updateMask();

    return mEntryWidget.processEvent(event);
}

Dimension PasswordEntryWidget::minimumSize() const
{
    return mEntryWidget.minimumSize();
}

void PasswordEntryWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

void PasswordEntryWidget::parented()
{
    mEntryWidget.setParent(this, Rectangle(widgetSize()));
}
