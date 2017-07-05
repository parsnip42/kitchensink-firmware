#include "ui/textentry.h"

#include "autorepeat.h"
#include "keycodes.h"
#include "keyprocessor.h"
#include "modifierstate.h"
#include "keymap/keymap.h"
#include "ui/keys.h"
#include "ui/surface.h"

#include <elapsedMillis.h>

namespace UI
{

TextEntry::TextEntry(Surface&      surface,
                     KeyProcessor& keyProcessor,
                     int           x,
                     int           y,
                     int           width,
                     const StrRef& text)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mX(x)
    , mY(y)
    , mWidth(width)
    , mText(text)
    , mCursorPosition(mText.size())
{ }

bool TextEntry::create()
{
    mSurface.rectangle(mX, mY, mWidth, Surface::kFontHeight + 3);
    
    paintText();

    AutoRepeat autoRepeat;
    ModifierState modifierState;

    bool entered(false);
    bool flash(false);
    
    while (1)
    {
        mKeyProcessor.poll(
            [&](const KeyEvent& event)
            {
                if (!modifierState.processEvent(event))
                {
                    autoRepeat.processEvent(event);
                }
            });
        
        if (((millis() >> 9) & 1) ^ flash)
        {
            flash = !flash;
            paintCursor(flash);
        }

        auto keyId(autoRepeat.activeKey());

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
                if (mCursorPosition < mText.size())
                {
                    ++mCursorPosition;
                }
                break;
                
            case KeyCodes::Home:
                mCursorPosition = 0;
                break;
                
            case KeyCodes::End:
                mCursorPosition = mText.size();
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
                if (mText.size() < 24)
                {
                    char newChar;
                    
                    if (modifierState.shift())
                    {
                        newChar = KeyMap::getEntry(keyId.value()).shift;
                    }
                    else
                    {
                        newChar = KeyMap::getEntry(keyId.value()).dflt; 
                    }

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

void TextEntry::processKey(const KeyId& keyId)
{
    
}

void TextEntry::paintText()
{
    mSurface.paintText(mX + 4, mY + 2, mText, 0xf, 0);
    mSurface.paintText(mX + 4 + (mText.size() * Surface::kFontWidth), mY + 2, " ", 0xf, 0);
}

void TextEntry::paintCursor(bool visible)
{
    auto fg(visible ? 0 : 0xf);
    auto bg(visible ? 0xf : 0);
    
    if (mCursorPosition < mText.size())
    {
        StrRef textRef(mText);
        auto cursorChar(textRef.substr(mCursorPosition, 1));
        
        mSurface.paintText(mX + 4 + (Surface::kFontWidth * mCursorPosition),
                           mY + 2, cursorChar, fg, bg);
    }
    else
    {        
        mSurface.paintText(mX + 4 + (mText.size() * Surface::kFontWidth),
                           mY + 2, " ", fg, bg);
    }
}

}
