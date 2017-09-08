#include "ui/textentrywidget.h"

#include "data/keycodes.h"
#include "data/keymap.h"
#include "ui/font.h"
#include "ui/keys.h"
#include "ui/rectangle.h"
#include "ui/renderutil.h"
#include "ui/surface.h"
#include "ui/colors.h"

TextEntryWidget::TextEntryWidget(Timer& timer)
    : cursorPosition(1000)
    , focused(true)
    , mFlashTimer(timer.createHandle())
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
}

void TextEntryWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(widgetSize());
    uint8_t fg(focused ? Colors::kFocused : Colors::kUnfocused);

    cursorPosition = std::min(cursorPosition, text.length());
    
    auto yOffset(0);

    if (Font::kHeight < size.height)
    {
        yOffset = (size.height - Font::kHeight) / 2;
    }
    
    RenderUtil::text(text,
                       2,
                       row - yOffset,
                       rasterLine,
                       fg,
                       Colors::kBackground);
    
    if (row >= 2 && row < size.height - 2)
    {
        StrRef textChar(" ");

        if (cursorPosition < text.length())
        {
            textChar = StrRef(text).substr(cursorPosition, 1);
        }

        uint8_t cursorFg(fg);
        uint8_t cursorBg(Colors::kBackground);

        if (mFlash)
        {
            std::swap(cursorFg, cursorBg);
        }
        
        RenderUtil::text(textChar,
                           2 + (cursorPosition * Font::kWidth),
                           row - yOffset,
                           rasterLine,
                           cursorFg,
                           cursorBg);
    }

    if (row == 0 || row == size.height - 1)
    {
        for (int i(0); i < size.width; ++i)
        {
            rasterLine[i] = fg;
        }
    }

    rasterLine[0] = fg;
    rasterLine[size.width - 1] = fg;
}

bool TextEntryWidget::processEvent(const Event& event)
{
    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;
        invalidateWidget();
        return true;
    }

    cursorPosition = std::min(cursorPosition, text.length());

    mVKeyboard.processEvent(event);

    if (event.is<KeyEvent>())
    {
        auto keyEvent(event.get<KeyEvent>());

        if (keyEvent.pressed)
        {
            mFlash = true;
            mFlashTimer.scheduleRepeating(1000, 500);

            switch (keyEvent.key)
            {
            case KeyCode::None:
                break;
                
            case KeyCode::Left:
                if (cursorPosition > 0)
                {
                    --cursorPosition;
                }
                break;
                
            case KeyCode::Right:
                if (cursorPosition < text.length())
                {
                    ++cursorPosition;
                }
                break;
                
            case KeyCode::Home:
                cursorPosition = 0;
                break;
                
            case KeyCode::End:
                cursorPosition = text.length();
                break;

            case KeyCode::Backspace:
                if (cursorPosition > 0)
                {
                    text.erase(text.begin() + cursorPosition - 1);
                
                    --cursorPosition;
                }
                break;
                
            default:
                if (text.length() < static_cast<std::size_t>(widgetSize().width / Font::kWidth) - 1)
                {
                    char newChar(mVKeyboard.consumeChar());
                    
                    if (newChar)
                    {
                        text.insert(text.begin() + cursorPosition, newChar);
                        
                        ++cursorPosition;
                    }
                    else
                    {
                        return false;
                    }
                }
                break;
            }
        }

        invalidateWidget();
        
        return true;
    }

    return false;
}

Dimension TextEntryWidget::minimumSize() const
{
    return Dimension(Font::kWidth + 4, Font::kHeight +4);
}
