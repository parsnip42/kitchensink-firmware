#ifndef INCLUDED_KEYMAP_H
#define INCLUDED_KEYMAP_H

#include <array>
#include <initializer_list>

#include <stdio.h>
#include <inttypes.h>

class KeyMap
{
public:
    static const size_t WIDTH  = 16;
    static const size_t HEIGHT = 5;

public:
    typedef std::array<uint32_t, WIDTH> Row;
    
public:
    explicit KeyMap(std::initializer_list<Row> rows);

public:
    const Row& operator[](size_t n) const;
    
private:
    typedef std::array<Row, HEIGHT> Rows;

    Rows rows_;

private:
    KeyMap(const KeyMap&) = delete;
    KeyMap& operator=(const KeyMap&) = delete;
};

inline
const KeyMap::Row& KeyMap::operator[](size_t n) const
{
    return rows_[n];
}

#endif
