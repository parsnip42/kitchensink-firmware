#include "ui/menu.h"
#include "autorepeat.h"
#include "timed.h"

#include <cstdint>

namespace UI
{

Menu::Menu(Surface& surface)
    : mSurface(surface)
{ }

void Menu::createMenu(const DataSource& dataSource,
                      KeyHandler&       keyHandler,
                      EventQueue&       eventQueue)
{
    const int selectionOffset(20);
    AutoRepeat autoRepeat(500);
    int selected(0);

    KeyId selectedKeyId;
    
    auto redraw([&](uint8_t fg = 0xf)
    {
        selectedKeyId = paintMenu(
            dataSource,
            selected,
            (selected * Surface::kFontHeight) - selectionOffset,
            fg,
            0);
    });

    for (auto fg(0); fg <= 0xf; ++fg)
    {
        Timed(10,
              [&]()
              {
                  redraw(fg);
              });
    }


    while (1)
    {
        keyHandler.poll(eventQueue);
        
        if (!eventQueue.empty())
        {
            autoRepeat.processEvent(eventQueue.pop());
        }

        auto keyId(autoRepeat.activeKey());
                
        if (keyId == KeyId(82))
        {
            for (int i(0); i < Surface::kFontHeight; ++i)
            {
                Timed(10,
                      [&]()
                      {
                          mSurface.scroll(Surface::kScrollMax - i);
                      },
                      [&]()
                      {
                          keyHandler.poll(eventQueue);
                      });
            }

            --selected;
            mSurface.scroll(0);
            redraw();
        }

        if (keyId == KeyId(81))
        {
            for (int i(0); i < Surface::kFontHeight; ++i)
            {
                Timed(10,
                      [&]()
                      {
                          mSurface.scroll(i);
                      },
                      [&]()
                      {
                          keyHandler.poll(eventQueue);
                      });
            }

            ++selected;
            mSurface.scroll(0);
            redraw();
        }
        
        if (keyId == KeyId(41))
        {
            break;
        }

        if (keyId == KeyId(40))
        {
            eventQueue.pushBack(KeyEvent(selectedKeyId, true));
            eventQueue.pushBack(KeyEvent(selectedKeyId, false));
            break;
        }
    }

    for (auto fg(0xf); fg >= 0; --fg)
    {
        Timed(10,
              [&]()
              {
                  redraw(fg);
              });
    }
}

KeyId Menu::paintMenu(const DataSource& dataSource,
                      int               selected,
                      int               offset,
                      uint8_t           fg,
                      uint8_t           bg)
{
    return paintMenu(dataSource,
                     selected,
                     offset,
                     0,
                     64,
                     fg,
                     bg);
}

KeyId Menu::paintMenu(const DataSource& dataSource,
                      int               selected,
                      int               offset,
                      int               start,
                      int               height,
                      uint8_t           fg,
                      uint8_t           bg)
{
    int len(240);
    
    const uint8_t colorMap[] =
    {
        uint8_t(bg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(fg | (fg << 4)),
    };
    
    const uint8_t invColorMap[] =
    {
        uint8_t(fg | (fg << 4)),
        uint8_t(fg | (bg << 4)),
        uint8_t(bg | (fg << 4)),
        uint8_t(bg | (bg << 4)),
    };

    mSurface.initRegion(28, start, len, height);

    int itemCount(dataSource.getItemCount());
    int pointRange(itemCount * Surface::kFontHeight);
    
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
        
        mSurface.paintTextLineC(text, len, line, colors);
    }

    return dataSource.getItem(selected).keyId;
}

}
