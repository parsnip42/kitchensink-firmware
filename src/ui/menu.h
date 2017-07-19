#ifndef INCLUDED_UI_MENU_H
#define INCLUDED_UI_MENU_H

#include "keyid.h"
#include "keyprocessor.h"
#include "types/strbuf.h"
#include "types/strostream.h"
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
        StrBuf<24> title;
        StrBuf<12> shortcut;
        KeyId      keyId;
    };
    
public:
    class DataSource
    {
    public:
        virtual void getItem(Item&       menuItem,
                             std::size_t index) const = 0;
        
        virtual std::size_t getItemCount() const = 0;
    };

public:
    Menu(const DataSource& dataSource,
         Surface&          surface,
         KeyProcessor&     keyProcessor);

public:
    void createMenu();

private:
    void moveSelection(int selectionOffset);
    
    void redraw();
    
    void paintMenu(int start,
                   int height);

    bool matchesFilter(const Item& item);
    
    void filteredItem(Item&       item,
                      std::size_t index);

    bool processExactFilterMatch();
    
    std::size_t filteredItemCount();
    
private:
    const DataSource& mDataSource;
    Surface&          mSurface;
    KeyProcessor&     mKeyProcessor;
    std::size_t       mSelected;
    StrBuf<12>        mFilter;
    
private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};


inline
Menu::Menu(const DataSource& dataSource,
           Surface&          surface,
           KeyProcessor&     keyProcessor)
    : mDataSource(dataSource)
    , mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mSelected(0)
    , mFilter()
{ }

}

#endif
