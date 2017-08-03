#include "ui/textentrywidget.h"

#include "data/keycodes.h"
#include "data/keymap.h"
#include "ui/font.h"
#include "ui/keys.h"
#include "ui/rectangle.h"
#include "ui/renderutil.h"
#include "ui/surface.h"
#include "ui/virtualkeyboard.h"

TextEntryWidget::TextEntryWidget(EventManager& eventManager)
    : cursorPosition(1000)
    , focused(true)
    , mFlashTimer(eventManager.timer.createHandle())
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

    invalidateWidget();
}

void TextEntryWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(getSize());
    uint8_t fg(focused ? 0xf : 0x7);
    
    cursorPosition = std::min(cursorPosition, text.length());
    
    if (row == 0 || row == size.height - 1)
    {
        for (int i(0); i < size.width; ++i)
        {
            rasterLine[i] = fg;
        }
    }

    rasterLine[0] = fg;
    rasterLine[size.width - 1] = fg;

    auto yOffset(0);

    if (Font::kHeight < size.height)
    {
        yOffset = (size.height - Font::kHeight) / 2;
    }
    
    RenderUtil::render(text,
                       2,
                       row - yOffset,
                       rasterLine,
                       fg,
                       0x0);
    
    if (row >= 2 && row < size.height - 2)
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
        
        RenderUtil::render(textChar,
                           2 + (cursorPosition * Font::kWidth),
                           row - yOffset,
                           rasterLine,
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
        invalidateWidget();
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
            if (text.length() < static_cast<std::size_t>(getSize().width / Font::kWidth) - 1)
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

    invalidateWidget();
}
