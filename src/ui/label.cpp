#include "label.h"

#include "types/strref.h"
#include "ui/surface.h"
#include "ui/rectangle.h"

namespace UI
{

Label::Label(Surface&         surface,
             const Rectangle& rect,
             const StrRef&    text,
             Justify          justify)
{
    auto x(rect.x);
    
    switch (justify)
    {
    case Justify::Right:
        x = (x + rect.width) - (Surface::kFontWidth * text.length());
        break;
        
    case Justify::Center:
        x = ((x + rect.width) - (Surface::kFontWidth * text.length())) / 2;
        break;
        
    default:
        break;
    }

    surface.paintText(x & ~3, rect.y, text, 0x7, 0x0);
}

}
