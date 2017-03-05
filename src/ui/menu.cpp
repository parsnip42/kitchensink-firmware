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
        [&](uint8_t fg = 0xf)
        {
            paintMenu(
                (mSelected * Surface::kFontHeight) - selectionOffset - scrollPos,
                scrollPos,
                Surface::kHeight,
                fg,
                0);                    
        });

    mSurface.clear();
    
    for (auto fg(0); fg <= 0xf; ++fg)
    {
         mKeyProcessor.delay(
             [&]()
             {
                 redraw(fg);
             }, 8);
    }

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
                Surface::kFontHeight,
                0xf,
                0);                       

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
                Surface::kFontHeight,
                0xf,
                0);

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
            DataSource::ItemText text;
            KeyId keyId;
            
            mDataSource.getItem(text,
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

    for (auto fg(0xf); fg >= 0; --fg)
    {
        mKeyProcessor.delay(
            [&]()
            {
                redraw(fg);
            }, 8);
    }
}

void Menu::paintMenu(int     offset,
                     int     start,
                     int     height,
                     uint8_t fg,
                     uint8_t bg)
{
    const Surface::ColorMap colorMap(fg, bg);
    const Surface::ColorMap invColorMap(bg, fg);

    const int itemCount(mDataSource.getItemCount());
    const int pointRange(itemCount * Surface::kFontHeight);
    
    mSelected = (itemCount + (mSelected % itemCount)) % itemCount;

    for (int y(start); y < (start + height); ++y)
    {
        DataSource::ItemText text;
        KeyId keyId;

        int point(y + offset);

        point = (pointRange + (point % pointRange)) % pointRange;
        
        int current(point / Surface::kFontHeight);
        
        const auto& colors(current != mSelected ? colorMap : invColorMap);

        
        mDataSource.getItem(text,
                            keyId,
                            current);

        auto line(point % Surface::kFontHeight);

        mSurface.initRegion(0, y, Surface::kWidth, 1);
        mSurface.paintTextLineC(text, Surface::kWidth, line, colors);
    }
}

}
