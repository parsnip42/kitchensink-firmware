#include "ui/textentrywidget.h"

#include "data/keycodes.h"
#include "keyprocessor.h"
#include "virtualkeyboard.h"
#include "data/keymap.h"
#include "ui/keys.h"
#include "ui/surface.h"
#include "ui/rectangle.h"

#include <elapsedMillis.h>

TextEntryWidget::TextEntryWidget(Surface&      surface,
                                 EventManager& eventManager)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mFlashTimer(eventManager.scheduleRepeating(500))
    , mCursorPosition(1000)
    , mFlash(false)
{ }

void TextEntryWidget::redraw()
{
    mSurface.rectangle(region.x, region.y, region.width, Surface::kFontHeight + 3);
    paintText();
}

void TextEntryWidget::processKeyEvent(const KeyEvent& event)
{
    VirtualKeyboard vKeyboard;

    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;
        paintCursor(mFlash);
    }

    mCursorPosition = std::min(mCursorPosition, text.length());
    
    vKeyboard.processKeyEvent(event);

    auto state(vKeyboard.readState());
    auto keyId(state.activeKey);

    if (keyId.type() == KeyId::Type::kKey && keyId.value())
    {
        if (mFlash)
        {
            paintCursor(false);
        }
            
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
                paintText();
                    
                --mCursorPosition;
            }
            break;
                
        default:
            if (text.length() < 24)
            {
                char newChar(state.activeChar);
                    
                if (newChar)
                {
                    text.insert(text.begin() + mCursorPosition, newChar);
                        
                    paintText();
                        
                    ++mCursorPosition;
                }
            }
            break;
        }    

        if (mFlash)
        {
            paintCursor(true);
        }
    }
}

void TextEntryWidget::paintText()
{
    mSurface.paintText(region.x + 4, region.y + 2, text, 0xf, 0);
    mSurface.paintText(region.x + 4 + (text.length() * Surface::kFontWidth), region.y + 2, " ", 0xf, 0);
}

void TextEntryWidget::paintCursor(bool visible)
{
    auto fg(visible ? 0 : 0xf);
    auto bg(visible ? 0xf : 0);
    
    if (mCursorPosition < text.length())
    {
        StrRef textRef(text);
        auto cursorChar(textRef.substr(mCursorPosition, 1));
        
        mSurface.paintText(region.x + 4 + (Surface::kFontWidth * mCursorPosition),
                           region.y + 2, cursorChar, fg, bg);
    }
    else
    {        
        mSurface.paintText(region.x + 4 + (text.length() * Surface::kFontWidth),
                           region.y + 2, " ", fg, bg);
    }
}
