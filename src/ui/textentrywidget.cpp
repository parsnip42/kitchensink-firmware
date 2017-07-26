#include "ui/textentrywidget.h"

#include "data/keycodes.h"
#include "keyprocessor.h"
#include "virtualkeyboard.h"
#include "data/keymap.h"
#include "ui/keys.h"
#include "ui/surface.h"
#include "ui/rectangle.h"

TextEntryWidget::TextEntryWidget(Surface&      surface,
                                 EventManager& eventManager)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mCursorPosition(1000)
    , mFlash(false)
    , mFocused(false)
{ }

void TextEntryWidget::redrawContent(bool focused)
{
    mFocused = focused;
    mFlash = focused;
    
    mSurface.rectangle(region.x, region.y, region.width, Surface::kFontHeight + 3, focused ? 0xf : 0x4);
    paintText();

    paintCursor(mFlash);
    mFlashTimer = focused ? std::move(mEventManager.scheduleRepeating(500)) : Timer::Handle();
}

void TextEntryWidget::processKeyEvent(const KeyEvent& event)
{
    VirtualKeyboard vKeyboard;

    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;
        paintCursor(mFlash);
        return;
    }

    mCursorPosition = std::min(mCursorPosition, text.length());
    
    vKeyboard.processKeyEvent(event);

    auto state(vKeyboard.readState());
    auto keyId(state.activeKey);

    if (keyId.type() == KeyId::Type::kKey && keyId.value())
    {
        mFlash = true;
        mFlashTimer = std::move(mEventManager.scheduleRepeating(500));

        paintCursor(false);

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
            if (text.length() < static_cast<std::size_t>(region.width / Surface::kFontWidth) - 2)
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

        paintCursor(true);
    }
}

void TextEntryWidget::paintText()
{
    uint8_t color(mFocused ? 0xf : 0x4);
    
    mSurface.paintText(region.x + 4, region.y + 2, text, color, 0);
    mSurface.paintText(region.x + 4 + (text.length() * Surface::kFontWidth), region.y + 2, " ", color, 0);
}

void TextEntryWidget::paintCursor(bool visible)
{
    uint8_t color(mFocused ? 0xf : 0x4);

    auto fg(visible ? 0 : color);
    auto bg(visible ? color : 0);
    
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
