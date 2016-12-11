#ifndef INCLUDED_UI_MENU_H
#define INCLUDED_UI_MENU_H

#include "keyid.h"
#include "keyprocessor.h"
#include "types/strref.h"
#include "ui/surface.h"

#include <cstdint>

class KeyProcessor;

namespace UI
{

class Menu
{
public:
    class Item
    {
    public:
        constexpr Item(const Types::StrRef& nText,
                       const KeyId&         nKeyId);

    public:
        Types::StrRef text;
        KeyId         keyId;
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
                    KeyProcessor&     keyProcessor);

private:
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
constexpr Menu::Item::Item(const Types::StrRef& nText,
                           const KeyId&         nKeyId)
    : text(nText)
    , keyId(nKeyId)
{ }

}

#endif
