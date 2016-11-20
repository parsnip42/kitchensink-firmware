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
                       const KeyId& nKeyId);

    public:
        const char* text;
        KeyId       keyId;
    };

public:
    class DataSource
    {
    public:
        virtual Item getItem(std::size_t index) const = 0;
        virtual std::size_t getItemCount() const = 0;
    };

public:
    explicit Menu(Surface& surface);

public:
    void createMenu(const DataSource& dataSource,
                    KeyHandler&       keyHandler,
                    EventQueue&       eventQueue);

private:
    KeyId paintMenu(const DataSource& dataSource,
                    int               selected,
                    int               offset,
                    uint8_t           fg,
                    uint8_t           bg);
    

    KeyId paintMenu(const DataSource& dataSource,
                    int               selected,
                    int               offset,
                    int               start,
                    int               end,
                    uint8_t           fg,
                    uint8_t           bg);
    
private:
    Surface& mSurface;

private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};


inline
constexpr Menu::Item::Item(const char*  nText,
                           const KeyId& nKeyId)
    : text(nText)
    , keyId(nKeyId)
{ }

}

#endif
