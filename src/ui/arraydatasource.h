#ifndef INCLUDED_ARRAYDATASOURCE_H
#define INCLUDED_ARRAYDATASOURCE_H

#include "ui/menu.h"

#include <cstdint>

class StrOStream;

namespace UI
{

class ArrayDataSource : public UI::Menu::DataSource
{
public:
    class Item
    {
    public:
        constexpr Item(const StrRef& nText,
                       const KeyId&  nKeyId);

    public:
        StrRef text;
        KeyId  keyId;
    };

public:
    template <std::size_t Size>
    constexpr ArrayDataSource(const Item (&menu)[Size]);

public:
    virtual void getItem(UI::Menu::Item& menuItem,
                         std::size_t     index) const;

    virtual std::size_t getItemCount() const;

private:
    const Item* mBegin;
    const Item* mEnd;
};


inline
constexpr ArrayDataSource::Item::Item(const StrRef& nText,
                                      const KeyId&  nKeyId)
    : text(nText)
    , keyId(nKeyId)
{ }


template <std::size_t Size>
inline
constexpr ArrayDataSource::ArrayDataSource(const UI::ArrayDataSource::Item (&menu)[Size])
    : mBegin(menu)
    , mEnd(menu + Size)
{ }

inline
void ArrayDataSource::getItem(UI::Menu::Item& menuItem,
                              std::size_t     index) const
{
    auto& item(*(mBegin + index));

    menuItem.title = item.text;
    menuItem.keyId = item.keyId;
}

inline
std::size_t ArrayDataSource::getItemCount() const
{
    return (mEnd - mBegin);
}

}

#endif
