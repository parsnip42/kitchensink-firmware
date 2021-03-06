#ifndef INCLUDED_LAYER_H
#define INCLUDED_LAYER_H

#include "event/event.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>

class Layer
{
private:
    static const std::size_t kColumns = Config::kLayerColumns;
    static const std::size_t kRows    = Config::kLayerRows;
    
public:
    typedef std::array<Event, kColumns> Row;
    typedef std::array<Row, kRows>      Mapping;
    
public:
    Layer() = default;

public:
    Event at(int row, int column) const;
    void set(int row, int column, const Event& event);
    void clear();
    
public:
    StrBuf<Config::kLayerNameLen> name;
    Mapping                       mapping;
};

#endif
