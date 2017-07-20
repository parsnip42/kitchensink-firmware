#include "ui/textentry.h"

#include "data/keycodes.h"
#include "keyprocessor.h"
#include "virtualkeyboard.h"
#include "data/keymap.h"
#include "ui/keys.h"
#include "ui/surface.h"
#include "ui/rectangle.h"

#include <elapsedMillis.h>

namespace UI
{

TextEntry::TextEntry(Surface&         surface,
                     KeyProcessor&    keyProcessor,
                     const Rectangle& rect,
                     const StrRef&    text)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mX(rect.x)
    , mY(rect.y)
    , mWidth(rect.width)
    , mText(text)
    , mCursorPosition(mText.length())
{
    mSurface.rectangle(mX, mY, mWidth, Surface::kFontHeight + 3);
    
    paintText();
}

bool TextEntry::focus()
{
    VirtualKeyboard vKeyboard;

    bool entered(false);
    bool flash(false);
    
    while (1)
    {
        mKeyProcessor.poll(vKeyboard);
        
        if (((millis() >> 9) & 1) ^ flash)
        {
            flash = !flash;
            paintCursor(flash);
        }

        auto state(vKeyboard.readState());
        auto keyId(state.activeKey);

        if (Keys::cancel(keyId))
        {
            entered = false;
            break;
        }

        if (Keys::ok(keyId))
        {
            entered = true;
            break;
        }

        if (keyId.type() == KeyId::Type::kKey && keyId.value())
        {
            if (flash)
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
                if (mCursorPosition < mText.length())
                {
                    ++mCursorPosition;
                }
                break;
                
            case KeyCodes::Home:
                mCursorPosition = 0;
                break;
                
            case KeyCodes::End:
                mCursorPosition = mText.length();
                break;

            case KeyCodes::Backspace:
                if (mCursorPosition > 0)
                {
                    mText.erase(mText.begin() + mCursorPosition - 1);
                    paintText();
                    
                    --mCursorPosition;
                }
                break;
                
            default:
                if (mText.length() < 24)
                {
                    char newChar(state.activeChar);
                    
                    if (newChar)
                    {
                        mText.insert(mText.begin() + mCursorPosition, newChar);
                        
                        paintText();
                        
                        ++mCursorPosition;
                    }
                }
                break;
            }    

            if (flash)
            {
                paintCursor(true);
            }
        }
    }

    return entered;
}

void TextEntry::paintText()
{
    mSurface.paintText(mX + 4, mY + 2, mText, 0xf, 0);
    mSurface.paintText(mX + 4 + (mText.length() * Surface::kFontWidth), mY + 2, " ", 0xf, 0);
}

void TextEntry::paintCursor(bool visible)
{
    auto fg(visible ? 0 : 0xf);
    auto bg(visible ? 0xf : 0);
    
    if (mCursorPosition < mText.length())
    {
        StrRef textRef(mText);
        auto cursorChar(textRef.substr(mCursorPosition, 1));
        
        mSurface.paintText(mX + 4 + (Surface::kFontWidth * mCursorPosition),
                           mY + 2, cursorChar, fg, bg);
    }
    else
    {        
        mSurface.paintText(mX + 4 + (mText.length() * Surface::kFontWidth),
                           mY + 2, " ", fg, bg);
    }
}

}
