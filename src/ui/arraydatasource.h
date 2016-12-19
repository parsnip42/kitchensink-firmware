#ifndef INCLUDED_ARRAYDATASOURCE_H
#define INCLUDED_ARRAYDATASOURCE_H

#include "ui/menu.h"

#include <cstdint>

namespace UI
{

class ArrayDataSource : public UI::Menu::DataSource
{
public:
    template <std::size_t Size>
    constexpr ArrayDataSource(const UI::Menu::Item (&menu)[Size]);

public:
    virtual UI::Menu::Item getItem(std::size_t index) const;
    virtual std::size_t getItemCount() const;

private:
    const UI::Menu::Item* mBegin;
    const UI::Menu::Item* mEnd;
};


template <std::size_t Size>
inline
constexpr ArrayDataSource::ArrayDataSource(const UI::Menu::Item (&menu)[Size])
    : mBegin(menu)
    , mEnd(menu + Size)
{ }

inline
UI::Menu::Item ArrayDataSource::getItem(std::size_t index) const
{
    return *(mBegin + index);
}

inline
std::size_t ArrayDataSource::getItemCount() const
{
    return (mEnd - mBegin);
}

}

#endif
