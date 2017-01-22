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

TextEntry::TextEntry(Surface&             surface,
                     KeyProcessor&        keyProcessor,
                     const Types::StrRef& text)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mText(text)
    , mCursorPosition(mText.size())
{ }

bool TextEntry::create()
{
    mSurface.rectangle(0, 20, (Surface::kFontWidth * 25) + 8, Surface::kFontHeight + 8);
    
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

        if (keyId.type() == KeyId::Type::kKey)
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
    mSurface.paintText(4, 24, mText, 0xf, 0);
    mSurface.paintText(4 + (mText.size() * Surface::kFontWidth), 24, " ", 0xf, 0);
}

void TextEntry::paintCursor(bool visible)
{
    auto fg(visible ? 0 : 0xf);
    auto bg(visible ? 0xf : 0);
    
    if (mCursorPosition < mText.size())
    {
        Types::StrRef textRef(mText);
        auto cursorChar(textRef.substr(mCursorPosition, 1));
        
        mSurface.paintText(4 + (Surface::kFontWidth * mCursorPosition),
                           24, cursorChar, fg, bg);
    }
    else
    {        
        mSurface.paintText(4 + (mText.size() * Surface::kFontWidth),
                           24, " ", fg, bg);
    }
}

}
