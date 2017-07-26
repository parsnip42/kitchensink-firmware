#ifndef INCLUDED_FOCUSUTIL_H
#define INCLUDED_FOCUSUTIL_H

#include <initializer_list>

class Widget;

namespace FocusUtil
{

bool next(Widget*&                              focus,
          const std::initializer_list<Widget*>& widgetList);

bool prev(Widget*&                              focus,
          const std::initializer_list<Widget*>& widgetList);

};

#endif
