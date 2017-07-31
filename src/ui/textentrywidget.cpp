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
                                 WidgetContainer& parent)
    : cursorPosition(1000)
    , focused(false)
    , mSurface(surface)
    , mEventManager(eventManager)
    , mParent(parent)
    , mFlashTimer(mEventManager.timer.createHandle())
    , mFlash(false)
{ }

void TextEntryWidget::setFocused(bool nFocused)
{
    focused = nFocused;
    mFlash = nFocused;
    
    if (focused)
    {
        mFlashTimer.scheduleRepeating(1000, 500);
    }
    else
    {
        mFlashTimer.cancel();
    }

    mParent.invalidateWidget(*this, region);
}

void TextEntryWidget::render(Surface::RowData& rowData, int row)
{
    uint8_t fg(focused ? 0xf : 0x7);
    
    cursorPosition = std::min(cursorPosition, text.length());
    
    if (row == 0 || row == region.height - 1)
    {
        for (int i(region.x); i < region.x + region.width; ++i)
        {
            rowData[i] = fg;
        }
    }

    rowData[region.x] = fg;
    rowData[region.x + region.width - 1] = fg;

    auto yOffset(0);

    if (Font::kHeight < region.height)
    {
        yOffset = (region.height - Font::kHeight) / 2;
    }
    
    Surface::render(text,
                    region.x + 2,
                    row - yOffset,
                    rowData,
                    fg,
                    0x0);
    
    if (row >= 2 && row < region.height - 2)
    {
        StrRef textChar(" ");

        if (cursorPosition < text.length())
        {
            textChar = StrRef(text).substr(cursorPosition, 1);
        }

        uint8_t cursorFg(fg);
        uint8_t cursorBg(0);

        if (mFlash)
        {
            std::swap(cursorFg, cursorBg);
        }
        
        Surface::render(textChar,
                        region.x + 2 + (cursorPosition * Font::kWidth),
                        row - yOffset,
                        rowData,
                        cursorFg,
                        cursorBg);
    }
}

void TextEntryWidget::processKeyEvent(const KeyEvent& event)
{
    VirtualKeyboard vKeyboard;

    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;
        mParent.invalidateWidget(*this, region);
        return;
    }

    cursorPosition = std::min(cursorPosition, text.length());
    
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
            if (cursorPosition > 0)
            {
                --cursorPosition;
            }
            break;
                
        case KeyCodes::Right:
            if (cursorPosition < text.length())
            {

                ++cursorPosition;
            }
            break;
                
        case KeyCodes::Home:
            cursorPosition = 0;
            break;
                
        case KeyCodes::End:
            cursorPosition = text.length();
            break;

        case KeyCodes::Backspace:
            if (cursorPosition > 0)
            {
                text.erase(text.begin() + cursorPosition - 1);
                
                --cursorPosition;
            }
            break;
                
        default:
            if (text.length() < static_cast<std::size_t>(region.width / Surface::kFontWidth) - 1)
            {
                char newChar(state.activeChar);
                    
                if (newChar)
                {
                    text.insert(text.begin() + cursorPosition, newChar);
                        
                    ++cursorPosition;
                }
            }
            break;
        }
    }

    mParent.invalidateWidget(*this, region);
}
