#ifndef INCLUDED_UI_MENU_H
#define INCLUDED_UI_MENU_H

#include "eventqueue.h"
#include "keyhandler.h"
#include "keyid.h"

#include "ui/surface.h"
#include <elapsedMillis.h>

#include <cstdint>

namespace UI
{

class Surface;

class Menu
{
public:
    class Item
    {
    public:
        constexpr Item(const char*  nText,
                       const KeyId& nKeyId)
            : text(nText)
            , keyId(nKeyId)
        { }

    public:
        const char* text;
        KeyId       keyId;
    };

public:
    class DataSource
    {
    public:
        virtual Item getItem(std::size_t index) = 0;
        virtual std::size_t getItemCount() = 0;
    };
    
public:
    class ArrayDataSource : public DataSource
    {
    public:
        ArrayDataSource(const Item* begin,
                        const Item* end)
            : mBegin(begin)
            , mEnd(end)
        { }

    public:
        virtual Item getItem(std::size_t index)
        {
            return *(mBegin + index);
        }

        virtual std::size_t getItemCount()
        {
            return (mEnd - mBegin);   
        }

    private:
        const Item* mBegin;
        const Item* mEnd;
    };

public:
    explicit Menu(Surface& surface);

public:
    void createMenu(DataSource& dataSource,
                    KeyHandler& keyHandler,
                    EventQueue& eventQueue);

private:
    KeyId paintMenu(DataSource& dataSource,
                    int         selected,
                    int         offset,
                    uint8_t     fg,
                    uint8_t     bg);
    

    KeyId paintMenu(DataSource& dataSource,
                    int         selected,
                    int         offset,
                    int         start,
                    int         end,
                    uint8_t     fg,
                    uint8_t     bg);
    
private:
    Surface& mSurface;

private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};


}

#endif
