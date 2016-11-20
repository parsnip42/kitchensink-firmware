#include "menudefinitions.h"

#include "keyid.h"

namespace
{

class ArrayDataSource : public UI::Menu::DataSource
{
public:
    template <std::size_t Size>
    ArrayDataSource(const UI::Menu::Item (&menu)[Size]);

public:
    virtual UI::Menu::Item getItem(std::size_t index) const;
    virtual std::size_t getItemCount() const;

private:
    const UI::Menu::Item* mBegin;
    const UI::Menu::Item* mEnd;
};


template <std::size_t Size>
inline
ArrayDataSource::ArrayDataSource(const UI::Menu::Item (&menu)[Size])
    : mBegin(menu)
    , mEnd(menu + Size)
{ }

UI::Menu::Item ArrayDataSource::getItem(std::size_t index) const
{
    return *(mBegin + index);
}

std::size_t ArrayDataSource::getItemCount() const
{
    return (mEnd - mBegin);
}


const UI::Menu::Item mainMenuItems[] =
{
    UI::Menu::Item("Macros", KeyId(4)),
    UI::Menu::Item("Layers", KeyId(5)),
    UI::Menu::Item("Display", KeyId(6)),
    UI::Menu::Item("Configuration", KeyId::Action(KeyId::ActionType::kMenu, 4)),
    UI::Menu::Item("System", KeyId(8)),
    UI::Menu::Item("Bootloader", KeyId::Action(KeyId::ActionType::kBuiltIn, 0))
};

const UI::Menu::Item configMenuItems[] =
{
    UI::Menu::Item("Autorepeat", KeyId()),
    UI::Menu::Item("Debounce", KeyId()),
    UI::Menu::Item("Interface", KeyId()),
    UI::Menu::Item("Multi Tap", KeyId()),
    UI::Menu::Item("Rollover", KeyId()),
};

const UI::Menu::Item emptyMenuItems[] =
{
    UI::Menu::Item("--", KeyId()),
};


const ArrayDataSource mainMenuSource(mainMenuItems);
const ArrayDataSource configMenuSource(configMenuItems);
const ArrayDataSource emptyMenuSource(emptyMenuItems);
}

namespace MenuDefinitions
{

const UI::Menu::DataSource& getDataSource(int id)
{
    switch (id)
    {
    case 0:
        return mainMenuSource;
    case 4:
        return configMenuSource;

    default:
        return emptyMenuSource;
    }
}

}
