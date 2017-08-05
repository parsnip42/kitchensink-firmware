#ifndef INCLUDED_WIDGETSET_H
#define INCLUDED_WIDGETSET_H

#include <array>
#include <cstdint>

class Widget;

template <std::size_t Size>
using WidgetSet = std::array<Widget*, Size>;

#endif
