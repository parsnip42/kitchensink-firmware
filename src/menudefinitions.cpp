#include "menudefinitions.h"

#include "keyboardstate.h"
#include "keyid.h"

namespace
{

const UI::Menu::Item mainMenuItems[] =
{
    UI::Menu::Item("Macros", KeyId(4)),
    UI::Menu::Item("Layers", KeyId::Action(KeyId::ActionType::kMenu, 2)),
    UI::Menu::Item("Modifiers", KeyId::Action(KeyId::ActionType::kMenu, 3)),
    UI::Menu::Item("Configuration", KeyId::Action(KeyId::ActionType::kMenu, 4)),
    UI::Menu::Item("System", KeyId::Action(KeyId::ActionType::kBuiltIn, 1)),
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

}

namespace
{
class LayerDataSource : public UI::Menu::DataSource
{
public:
    LayerDataSource() {}

public:
    virtual UI::Menu::Item getItem(std::size_t index) const
    {
        return UI::Menu::Item(state->layerStack[index].name, KeyId(8));
    }
    
    virtual std::size_t getItemCount() const
    {
        return LayerStack::MaxLayers;
    }

public:
    KeyboardState* state;
};

LayerDataSource layerDataSource;
}

namespace
{
class ModifierDataSource : public UI::Menu::DataSource
{
public:
    ModifierDataSource() {}

public:
    virtual UI::Menu::Item getItem(std::size_t index) const
    {
        return UI::Menu::Item(state->modifierSet[index].name(),
                              KeyId::Modifier(KeyId::ModifierType::kToggle, index));
    }
    
    virtual std::size_t getItemCount() const
    {
        return 30;
    }

public:
    KeyboardState* state;
};

ModifierDataSource modifierDataSource;
}

MenuDefinitions::MenuDefinitions(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
    , mMainMenuSource(mainMenuItems)
    , mConfigMenuSource(configMenuItems)
    , mEmptyMenuSource(emptyMenuItems)
{
    layerDataSource.state = &mKeyboardState;
    modifierDataSource.state = &mKeyboardState;
}

const UI::Menu::DataSource& MenuDefinitions::getDataSource(int id) const
{
    switch (id)
    {
    case 0:
        return mMainMenuSource;
    case 2:
        return layerDataSource;
    case 3:
        return modifierDataSource;
    case 4:
        return mConfigMenuSource;
    default:
        return mEmptyMenuSource;
    }
}

