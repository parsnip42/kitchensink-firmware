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
    class DataSource
    {
    public:
        virtual void getItem(const StrOStream& title,
                             KeyId&            keyId,
                             std::size_t       index) const = 0;
        
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

    bool matchesFilter(const StrRef& title);
    
    void filteredItem(const StrOStream& title,
                      KeyId&            keyId,
                      std::size_t       index);
    
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
