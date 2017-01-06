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

bool TextEntry::create(const Types::StrRef& title,
                       const Types::StrRef& text)
{
    mText = text;
    
    mSurface.clear();

    mSurface.paintText(0, 0, title, 0xf, 0);

    mSurface.rectangle(0, 20, (Surface::kFontWidth * 25) + 8, Surface::kFontHeight + 8);

    std::size_t cursorPosition(mText.size());
    
    auto refresh([&](bool cursor = false)
    {             
        mSurface.paintText(4, 24, mText, 0xf, 0);
        mSurface.paintText(4 + (mText.size() * Surface::kFontWidth),
                           24, " ", cursor ? 0 : 0xf, cursor ? 0xf : 0);
    });

    auto paintCursor([&](bool cursor)
    {
        auto fg(cursor ? 0 : 0xf);
        auto bg(cursor ? 0xf : 0);
        
        if (cursorPosition < mText.size())
        {
            Types::StrRef textRef(mText);
            auto cursorChar(textRef.substr(cursorPosition, 1));
            
            mSurface.paintText(4 + (Surface::kFontWidth * cursorPosition), 24, cursorChar, fg, bg);
        }
        else
        {        
            mSurface.paintText(4 + (mText.size() * Surface::kFontWidth),
                               24, " ", fg, bg);
        }
    });
    
    refresh();

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

        auto keyId(autoRepeat.activeKey());

        if (Keys::cancel(keyId))
        {
            entered = false;
            break;
        }
        else if (keyId.type() == KeyId::Type::kKey && keyId.value() != 0)
        {
            if (keyId.value() == KeyCodes::Left)
            {
                if (cursorPosition > 0)
                {
                    paintCursor(false);
                    --cursorPosition;
                    paintCursor(true);
                }
            }
            else if (keyId.value() == KeyCodes::Right)
            {
                if (cursorPosition < mText.size())
                {
                    paintCursor(false);
                    ++cursorPosition;
                    paintCursor(true);
                }
            }
            else if (keyId.value() == KeyCodes::Backspace)
            {
                if (cursorPosition > 0)
                {
                    paintCursor(false);
                    mText.erase(mText.begin() + cursorPosition - 1);
                    refresh();
                    
                    --cursorPosition;
                    paintCursor(true);
                }
            }
            else if (keyId.value() == KeyCodes::Enter)
            {
                entered = true;
                break;
            }
            else if (mText.size() < 24)
            {
                paintCursor(false);

                char newChar;
                
                if (modifierState.shift())
                {
                    newChar = KeyMap::getEntry(keyId.value()).shift;
                }
                else
                {
                    newChar = KeyMap::getEntry(keyId.value()).dflt; 
                }
                
                mText.insert(mText.begin() + cursorPosition, newChar);

                refresh();

                ++cursorPosition;
                
                paintCursor(true);
            }
        }

        if (((millis() >> 9) & 1) ^ flash)
        {
            paintCursor(flash);
            flash = !flash;
        }
    }

    mSurface.clear();

    return entered;
}

}
