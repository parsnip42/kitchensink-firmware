#include "ui/entrywidget.h"

#include "data/keycode.h"
#include "data/keymap.h"
#include "ui/font.h"
#include "ui/keys.h"
#include "ui/rectangle.h"
#include "ui/renderutil.h"
#include "ui/surface.h"
#include "ui/colors.h"


EntryWidget::EntryWidget(TimerManager&   timer,
                         Content* nContent)
    : content(nContent)
    , mFlashTimer(timer.createTimer())
    , mFocused(true)
    , mFlash(false)
    , mCursorPosition(1000)
{ }

void EntryWidget::setFocused(bool focused)
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

void EntryWidget::render(const RasterLine& rasterLine, int row)
{
    const auto& text(content->textContent());
    auto size(widgetSize());
    uint8_t fg(mFocused ? Colors::kFocused : Colors::kUnfocused);

    mCursorPosition = std::min(mCursorPosition, text.length());
    
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

        if (mCursorPosition < text.length())
        {
            textChar = StrRef(text).substr(mCursorPosition, 1);
        }

        uint8_t cursorFg(fg);
        uint8_t cursorBg(Colors::kBackground);

        if (mFlash)
        {
            std::swap(cursorFg, cursorBg);
        }
        
        RenderUtil::text(textChar,
                         2 + (mCursorPosition * Font::kWidth),
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

bool EntryWidget::processEvent(const Event& event)
{
    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;
        invalidateWidget();
        return true;
    }

    if (event.is<KeyEvent>() && event.get<KeyEvent>().pressed)
    {
        mFlash = true;
        mFlashTimer.scheduleRepeating(1000, 500);
    }

    const auto& text(content->textContent());
    
    mCursorPosition = std::min(mCursorPosition, text.length());

    if (processVKeyboard(event))
    {
        return true;
    }
    else if (processCursor(event))
    {
        return true;
    }
    
    return false;
}

bool EntryWidget::processVKeyboard(const Event& event)
{
    const auto& text(content->textContent());

    if (mVKeyboard.processEvent(event))
    {
        if (text.length() < static_cast<std::size_t>(widgetSize().width / Font::kWidth) - 1)
        {
            char newChar(mVKeyboard.consumeChar());
            
            if (newChar)
            {
                if (content->insertChar(newChar, mCursorPosition))
                {
                    ++mCursorPosition;
                }
            }
        }

        invalidateWidget();

        return true;
    }

    return false;
}

bool EntryWidget::processCursor(const Event& event)
{
    const auto& text(content->textContent());

    if (event.is<KeyEvent>())
    {
        auto keyEvent(event.get<KeyEvent>());

        switch (keyEvent.key)
        {
        case KeyCode::Left:
            if (keyEvent.pressed)
            {
                if (mCursorPosition > 0)
                {
                    --mCursorPosition;
                }
                
                invalidateWidget();
            }
            return true;
                
        case KeyCode::Right:
            if (keyEvent.pressed)
            {
                if (mCursorPosition < text.length())
                {
                    ++mCursorPosition;
                }
                
                invalidateWidget();
            }
            return true;
            
        case KeyCode::Home:
            if (keyEvent.pressed)
            {
                mCursorPosition = 0;
                invalidateWidget();
            }
            return true;
                
        case KeyCode::End:
            if (keyEvent.pressed)
            {
                mCursorPosition = text.length();
                invalidateWidget();
            }
            return true;

        case KeyCode::Backspace:
            if (keyEvent.pressed)
            {
                if (mCursorPosition > 0)
                {
                    if (content->eraseChar(mCursorPosition))
                    {
                        --mCursorPosition;
                    }
                }
                
                invalidateWidget();
            }
            return true;

        default:
            break;
        }
    }

    return false;
}

Dimension EntryWidget::minimumSize() const
{
    return Dimension(Font::kWidth + 4, Font::kHeight +4);
}
