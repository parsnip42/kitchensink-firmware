#ifndef INCLUDED_MENUDEFINITIONS_H
#define INCLUDED_MENUDEFINITIONS_H

#include "ui/menuscreen.h"
#include "types/arrayobjectsource.h"

class StrOStream;
class KeyboardState;

namespace Impl
{

class MacroDataSource : public MenuScreen::DataSource
{
public:
    explicit MacroDataSource(const KeyboardState& keyboardState);

public:
    virtual MenuScreen::Item operator[](std::size_t index) const;
    virtual std::size_t size() const;

public:
    const KeyboardState& mKeyboardState;

private:
    MacroDataSource(const MacroDataSource&) = delete;
    MacroDataSource& operator=(const MacroDataSource&) = delete;
};


class EditMacroDataSource : public MenuScreen::DataSource
{
public:
    explicit EditMacroDataSource(const KeyboardState& keyboardState);

public:
    virtual MenuScreen::Item operator[](std::size_t index) const;
    virtual std::size_t size() const;

public:
    const KeyboardState& mKeyboardState;

private:
    EditMacroDataSource(const EditMacroDataSource&) = delete;
    EditMacroDataSource& operator=(const EditMacroDataSource&) = delete;
};

class MultiKeyDataSource : public MenuScreen::DataSource
{
public:
    explicit MultiKeyDataSource(const KeyboardState& keyboardState);

public:
    virtual MenuScreen::Item operator[](std::size_t index) const;
    virtual std::size_t size() const;

public:
    const KeyboardState& mKeyboardState;
    
private:
    MultiKeyDataSource(const MultiKeyDataSource&) = delete;
    MultiKeyDataSource& operator=(const MultiKeyDataSource&) = delete;
};


class SmartKeyDataSource : public MenuScreen::DataSource
{
public:
    explicit SmartKeyDataSource(const KeyboardState& keyboardState);

public:
    virtual MenuScreen::Item operator[](std::size_t index) const;
    virtual std::size_t size() const;

public:
    const KeyboardState& mKeyboardState;
    
private:
    SmartKeyDataSource(const SmartKeyDataSource&) = delete;
    SmartKeyDataSource& operator=(const SmartKeyDataSource&) = delete;
};

class KeyDataSource : public MenuScreen::DataSource
{
public:
    explicit KeyDataSource(const KeyboardState& keyboardState);

public:
    virtual MenuScreen::Item operator[](std::size_t index) const;
    virtual std::size_t size() const;

public:
    const KeyboardState& mKeyboardState;

private:
    KeyDataSource(const KeyDataSource&) = delete;
    KeyDataSource& operator=(const KeyDataSource&) = delete;
};

}

class MenuDefinitions
{
public:
    explicit MenuDefinitions(const KeyboardState& keyboardState);

public:
    StrRef getTitle(int id) const;
    const MenuScreen::DataSource& getDataSource(int id) const;

private:
    const ArrayObjectSource<MenuScreen::Item> mMainMenuSource;
    const ArrayObjectSource<MenuScreen::Item> mSystemMenuSource;
    const ArrayObjectSource<MenuScreen::Item> mEmptyMenuSource;

    const Impl::MacroDataSource     mMacroDataSource;
    const Impl::EditMacroDataSource mEditMacroDataSource;
    const Impl::MultiKeyDataSource  mMultiKeyDataSource;
    const Impl::SmartKeyDataSource  mSmartKeyDataSource;
    const Impl::KeyDataSource       mKeyDataSource;

private:
    MenuDefinitions(const MenuDefinitions&) = delete;
    MenuDefinitions& operator=(const MenuDefinitions&) = delete;
};

#endif
