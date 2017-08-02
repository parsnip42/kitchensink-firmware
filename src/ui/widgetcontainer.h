#ifndef INCLUDED_WIDGETCONTAINER_H
#define INCLUDED_WIDGETCONTAINER_H

class Widget;
class Rectangle;

class WidgetContainer
{
public:
    WidgetContainer() = default;
    virtual ~WidgetContainer() = default;
    
public:
    virtual void regionInvalidated(const Rectangle& region) = 0;
};

#endif
