#include "ui/menu.h"
#include "ui/keys.h"
#include "autorepeat.h"

#include <cstdint>

namespace UI
{

void Menu::createMenu()
{
    constexpr int selectionOffset(((Surface::kHeight % Surface::kFontHeight) / 2) + Surface::kFontHeight);
    AutoRepeat autoRepeat;

    uint8_t scrollPos(0);    

    auto redraw(
        [&]()
        {
            paintMenu(
                (mSelected * Surface::kFontHeight) - selectionOffset - scrollPos,
                scrollPos,
                Surface::kHeight);                    
        });

    mSurface.clear();
    redraw();
    
    while (1)
    {
        mKeyProcessor.poll(
            [&](const KeyEvent& event)
            {
                autoRepeat.processEvent(event);
            });

        auto keyId(autoRepeat.activeKey());
                
        if (Keys::up(keyId))
        {
            paintMenu(
                (mSelected * Surface::kFontHeight) - selectionOffset - scrollPos,
                scrollPos - Surface::kFontHeight,
                Surface::kFontHeight);                       

            for (int i(0); i < Surface::kFontHeight; ++i)
            {
                mKeyProcessor.delay(
                    [&]()
                    {
                        --scrollPos;
                        mSurface.scroll(scrollPos);
                    }, 4);
            }

            --mSelected;
            redraw();
        }
        else if (Keys::down(keyId))
        {
            paintMenu(
                (mSelected * Surface::kFontHeight) - selectionOffset - scrollPos,
                Surface::kHeight + scrollPos,
                Surface::kFontHeight);

            for (int i(0); i < Surface::kFontHeight; ++i)
            {
                mKeyProcessor.delay(
                    [&]()
                    {
                        ++scrollPos;
                        mSurface.scroll(scrollPos);
                    }, 4);
            }
            
            ++mSelected;
            redraw();
        }
        else if (Keys::ok(keyId))
        {
            StrBuf<20> text;
            StrOStream ostream(text);
            KeyId keyId;
            
            mDataSource.getItem(ostream,
                                keyId,
                                mSelected);
            
            mKeyProcessor.pushEvent(KeyEvent(keyId, true));
            mKeyProcessor.pushEvent(KeyEvent(keyId, false));
            break;
        }
        else if (Keys::cancel(keyId))
        {
            break;
        }
    }

    mSurface.clear();
}

void Menu::paintMenu(int offset,
                     int start,
                     int height)
{
    static const Surface::ColorMap colorMap(0xf, 0x0);
    static const Surface::ColorMap invColorMap(0x0, 0xf);

    const int itemCount(mDataSource.getItemCount());
    const int pointRange(itemCount * Surface::kFontHeight);
    
    mSelected = (itemCount + (mSelected % itemCount)) % itemCount;

    for (int y(start); y < (start + height); ++y)
    {
        StrBuf<20> text;
        StrOStream ostream(text);

        KeyId keyId;

        int point(y + offset);

        point = (pointRange + (point % pointRange)) % pointRange;
        
        int current(point / Surface::kFontHeight);
        
        const auto& colors(current != mSelected ? colorMap : invColorMap);

        
        mDataSource.getItem(ostream,
                            keyId,
                            current);

        auto line(point % Surface::kFontHeight);

        mSurface.initRegion(0, y, Surface::kWidth, 1);
        mSurface.paintTextLineC(text, Surface::kWidth, line, colors);
    }
}

}
