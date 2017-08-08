#ifndef INCLUDED_MENUWIDGET_H
#define INCLUDED_MENUWIDGET_H

#include "ui/dimension.h"
#include "ui/menuitemwidget.h"
#include "ui/surface.h"
#include "ui/virtualkeyboard.h"
#include "ui/widget.h"
#include "ui/widgetcontainer.h"
#include "types/filterindex.h"
#include "types/objectsource.h"
#include "types/strbuf.h"

#include <cstdint>

class MenuItemWidget;

class MenuWidget : public Widget
                 , public WidgetContainer
{
public:
    typedef ObjectSource<MenuItemWidget> DataSource;

public:
    explicit MenuWidget(const DataSource& dataSource);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void regionInvalidated(const Rectangle& region) override;

public:
    int selectedIndex() const;
    void update();
    
private:
    void moveSelection(int direction);
    void populateMenuItem(int index);
    void applyFilter();
    
public:
    FilterIndex<300> filterIndex;
    StrBuf<24>       filterStr;

private:
    const DataSource& mDataSource;
    int               mSelectedIndex;
    bool              mFocused;
    MenuItemWidget    mWidget;
    int               mWidgetIndex;
    VirtualKeyboard   mVKeyboard;
};

#endif
