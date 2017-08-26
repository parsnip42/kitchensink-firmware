#ifndef INCLUDED_BUTTONWIDGET_H
#define INCLUDED_BUTTONWIDGET_H

#include "ui/widget.h"
#include "types/strbuf.h"
#include "types/strref.h"

class ButtonWidget : public Widget
{
public:
    explicit ButtonWidget(const StrRef& nText);

public:
    virtual bool processEvent(const Event& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    StrBuf<24> text;
    bool       activated;
    
private:
    bool mFocused;
};

#endif
