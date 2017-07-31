#include "ui/focusutil.h"

#include "ui/widget.h"

namespace FocusUtil
{

bool next(Widget*&                              focus,
          const std::initializer_list<Widget*>& widgetList)
{
    auto it(widgetList.begin());
    
    while (it != widgetList.end())
    {
        if (*it == focus)
        {
            auto last(*it++);
            
            if (it != widgetList.end())
            {
                last->setFocused(false);
                (*it)->setFocused(true);

                focus = (*it);
                return true;
            }
        }
        else
        {
            ++it;
        }
    }

    return false;
}

bool prev(Widget*&                              focus,
          const std::initializer_list<Widget*>& widgetList)
{
    Widget* last(nullptr);

    for (auto widget : widgetList)
    {
        if (focus == widget && last)
        {
            widget->setFocused(false);
            last->setFocused(true);
            
            focus = last;
            return true;
        }

        last = widget;
    }
    
    return false;
}

}
