#ifndef INCLUDED_LABEL_H
#define INCLUDED_LABEL_H

class StrRef;
class Surface;
class Rectangle;

class Label
{
public:
    enum Justify
    {
        Left = 0,
        Right = 1,
        Center = 2
    };
    
public:
    Label(Surface&         surface,
          const Rectangle& rect,
          const StrRef&    text,
          Justify          justify);
};

#endif /* INCLUDED_LABEL_H */
