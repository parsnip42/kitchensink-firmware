#include "ui/menu.h"
#include "ui/keys.h"
#include "autorepeat.h"

#include <cstdint>

namespace UI
{

Menu::Menu(Surface& surface)
    : mSurface(surface)
{ }

void Menu::createMenu(const DataSource& dataSource,
                      KeyProcessor&     keyProcessor)
{
    const int selectionOffset(20);
    AutoRepeat autoRepeat(500);
    int selected(0);

    KeyId selectedKeyId;

    uint8_t scrollPos(0);    

    auto redraw(
        [&](uint8_t fg = 0xf)
        {
            selectedKeyId = paintMenu(
                dataSource,
                selected,
                (selected * Surface::kFontHeight) - selectionOffset - scrollPos,
                scrollPos,
                Surface::kHeight,
                fg,
                0);                    
        });

    mSurface.clear();
    
    for (auto fg(0); fg <= 0xf; ++fg)
    {
         keyProcessor.delay(
             [&]()
             {
                 redraw(fg);
             }, 8);
    }

    while (1)
    {
        keyProcessor.poll(
            [&](const KeyEvent& event)
            {
                autoRepeat.processEvent(event);
            });

        auto keyId(autoRepeat.activeKey());
                
        if (Keys::up(keyId))
        {
            paintMenu(
                dataSource,
                selected,
                (selected * Surface::kFontHeight) - selectionOffset - scrollPos,
                scrollPos - Surface::kFontHeight,
                Surface::kFontHeight,
                0xf,
                0);                       

            for (int i(0); i < Surface::kFontHeight; ++i)
            {
                keyProcessor.delay(
                    [&]()
                    {
                        --scrollPos;
                        mSurface.scroll(scrollPos);
                    }, 8);
            }

            --selected;
            redraw();
        }
        else if (Keys::down(keyId))
        {
            paintMenu(
                dataSource,
                selected,
                (selected * Surface::kFontHeight) - selectionOffset - scrollPos,
                Surface::kHeight + scrollPos,
                Surface::kFontHeight,
                0xf,
                0);

            for (int i(0); i < Surface::kFontHeight; ++i)
            {
                keyProcessor.delay(
                    [&]()
                    {
                        ++scrollPos;
                        mSurface.scroll(scrollPos);
                    }, 8);
            }
            
            ++selected;
            redraw();
        }
        else if (Keys::ok(keyId))
        {
            keyProcessor.pushEvent(KeyEvent(selectedKeyId, true));
            keyProcessor.pushEvent(KeyEvent(selectedKeyId, false));
            break;
        }
        else if (Keys::cancel(keyId))
        {
            break;
        }
    }

    for (auto fg(0xf); fg >= 0; --fg)
    {
        keyProcessor.delay(
            [&]()
            {
                redraw(fg);
            }, 8);
    }
}

KeyId Menu::paintMenu(const DataSource& dataSource,
                      int               selected,
                      int               offset,
                      int               start,
                      int               height,
                      uint8_t           fg,
                      uint8_t           bg)
{
    const Surface::ColorMap colorMap(fg, bg);
    const Surface::ColorMap invColorMap(bg, fg);

    const int itemCount(dataSource.getItemCount());
    const int pointRange(itemCount * Surface::kFontHeight);
    
    selected = (itemCount + (selected % itemCount)) % itemCount;

    for (int y(start); y < (start + height); ++y)
    {
        int point(y + offset);

        point = (pointRange + (point % pointRange)) % pointRange;
        
        int current(point / Surface::kFontHeight);
        
        const auto& colors(current != selected ? colorMap : invColorMap);

        auto entry(dataSource.getItem(current));
        auto text(entry.text);

        auto line(point % Surface::kFontHeight);

        mSurface.initRegion(28, y, Surface::kWidth, 1);
        mSurface.paintTextLineC(text, Surface::kWidth, line, colors);
    }

    return dataSource.getItem(selected).keyId;
}

}
