#ifndef INCLUDED_UI_COMBO_H
#define INCLUDED_UI_COMBO_H

#include "types/strbuf.h"

class KeyProcessor;

namespace UI { class Surface; }

namespace UI
{

class Combo
{
public:
    class DataSource
    {
    public:
        typedef Types::StrBuf<20> ItemText;
        
    public:
        virtual void getItem(ItemText&   text,
                             std::size_t index) const = 0;
        
        virtual std::size_t getItemCount() const = 0;
    };

public:
    Combo(Surface&           surface,
          KeyProcessor&      keyProcessor,
          int                x,
          int                y,
          int                width,
          Combo::DataSource& dataSource,
          std::size_t        selectedItem);

public:    
    bool create();
    
    std::size_t selectedItem() const;
    
private:
    void paintSelection();
    
private:
    Surface&           mSurface;
    KeyProcessor&      mKeyProcessor;
    int                mX;
    int                mY;
    int                mWidth;
    Combo::DataSource& mDataSource;
    std::size_t        mSelectedItem;

private:
    Combo(const Combo&) = delete;
    Combo& operator=(const Combo&) = delete;
};


inline
std::size_t Combo::selectedItem() const
{
    return mSelectedItem;
}

}

#endif
