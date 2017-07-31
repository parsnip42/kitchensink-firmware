#include "ui/textentrywidget.h"

#include "data/keycodes.h"
#include "keyprocessor.h"
#include "virtualkeyboard.h"
#include "data/keymap.h"
#include "ui/keys.h"
#include "ui/surface.h"
#include "ui/rectangle.h"

TextEntryWidget::TextEntryWidget(Surface&         surface,
                                 EventManager&    eventManager,
                                 WidgetContainer& widgetContainer)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mWidgetContainer(widgetContainer)
    , mFlashTimer(mEventManager.timer.createHandle())
    , mCursorPosition(1000)
    , mFlash(false)
    , mFocused(false)
{ }

void TextEntryWidget::redrawContent(bool focused)
{
    mFocused = focused;
    mFlash = focused;
    
    if (focused)
    {
        mFlashTimer.scheduleRepeating(1000, 500);
    }
    else
    {
        mFlashTimer.cancel();
    }
}

void TextEntryWidget::render(Surface::RowData& rowData, int row) const
{
    if (row == 0 || row == region.height - 1)
    {
        for (int i(region.x); i < region.x + region.width; ++i)
        {
            rowData[i] = 0xf;
        }
    }

    rowData[region.x] = 0xf;
    rowData[region.x + region.width - 1] = 0xf;

    auto yOffset(0);

    if (Font::kHeight < region.height)
    {
        yOffset = (region.height - Font::kHeight) / 2;
    }
    
    Surface::render(text, region.x + 2, row - yOffset, rowData, 0xf, 0x0);
    
    if (row >= 2 && row < region.height - 2)
    {
        StrRef textChar(" ");

        if (mCursorPosition < text.length())
        {
            textChar = StrRef(text).substr(mCursorPosition, 1);
        }

        uint8_t fg(0xf);
        uint8_t bg(0);

        if (mFlash)
        {
            std::swap(fg, bg);
        }
        
        Surface::render(textChar, region.x + 2 + (mCursorPosition * Font::kWidth), row - yOffset, rowData, fg, bg);
    }
}

void TextEntryWidget::processKeyEvent(const KeyEvent& event)
{
    VirtualKeyboard vKeyboard;

    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;
        mWidgetContainer.invalidateWidget(*this, region);
        return;
    }

    mCursorPosition = std::min(mCursorPosition, text.length());
    
    vKeyboard.processKeyEvent(event);

    const auto& state(vKeyboard.state);
    auto keyId(state.activeKey);

    if (keyId.type() == KeyId::Type::kKey && keyId.value() && event.pressed)
    {
        mFlash = true;
        mFlashTimer.scheduleRepeating(1000, 500);

        switch (keyId.value())
        {
        case 0:
            break;
                
        case KeyCodes::Left:
            if (mCursorPosition > 0)
            {
                --mCursorPosition;
            }
            break;
                
        case KeyCodes::Right:
            if (mCursorPosition < text.length())
            {

                ++mCursorPosition;
            }
            break;
                
        case KeyCodes::Home:
            mCursorPosition = 0;
            break;
                
        case KeyCodes::End:
            mCursorPosition = text.length();
            break;

        case KeyCodes::Backspace:
            if (mCursorPosition > 0)
            {
                text.erase(text.begin() + mCursorPosition - 1);
                
                --mCursorPosition;
            }
            break;
                
        default:
            if (text.length() < static_cast<std::size_t>(region.width / Surface::kFontWidth) - 1)
            {
                char newChar(state.activeChar);
                    
                if (newChar)
                {
                    text.insert(text.begin() + mCursorPosition, newChar);
                        
                    ++mCursorPosition;
                }
            }
            break;
        }
    }

    mWidgetContainer.invalidateWidget(*this, region);
}
