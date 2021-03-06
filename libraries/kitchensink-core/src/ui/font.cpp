#include "ui/font.h"

#include <cstdint>

namespace Font
{

const uint8_t fontData[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x00,0x00,
    0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x20,0x50,0x50,0x20,0x48,0x20,0x20,0x10,0x40,0x00,
    0x00,0x00,0x00,0x00,0x08,0x70,0x20,0x70,0x70,0x08,0xf8,0x70,0xf8,0x70,0x70,0x00,0x00,0x00,0x00,0x00,
    0x70,0x70,0x70,0xf0,0x70,0xe0,0xf8,0xf8,0x70,0x88,0x70,0x38,0x88,0x80,0x88,0x88,0x70,0xf0,0x70,0xf0,
    0x70,0xf8,0x88,0x88,0x88,0x88,0x88,0xf8,0x70,0x40,0x70,0x50,0x00,0x00,0x00,0x80,0x00,0x08,0x00,0x18,
    0x00,0x80,0x20,0x08,0x40,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
    0x18,0x20,0x60,0xa8,0x0c,0x20,0x50,0x50,0x70,0xa8,0x50,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x08,
    0x88,0x60,0x88,0x88,0x18,0x80,0x80,0x08,0x88,0x88,0x00,0x00,0x08,0x00,0x40,0x88,0x88,0x88,0x88,0x88,
    0x90,0x80,0x80,0x88,0x88,0x20,0x10,0x90,0x80,0xd8,0x88,0x88,0x88,0x88,0x88,0x88,0x20,0x88,0x88,0x88,
    0x88,0x88,0x08,0x40,0x40,0x10,0x88,0x00,0x00,0x00,0x80,0x00,0x08,0x00,0x20,0x00,0x80,0x00,0x00,0x40,
    0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x10,0x90,0x0c,
    0x20,0x00,0xf8,0xa8,0x50,0x50,0x00,0x40,0x10,0x50,0x20,0x00,0x00,0x00,0x10,0x98,0x20,0x88,0x08,0x28,
    0x80,0x80,0x08,0x88,0x88,0x20,0x20,0x10,0xf8,0x20,0x88,0x98,0x88,0x88,0x80,0x88,0x80,0x80,0x80,0x88,
    0x20,0x10,0xa0,0x80,0xa8,0xc8,0x88,0x88,0x88,0x88,0x80,0x20,0x88,0x88,0x88,0x50,0x50,0x10,0x40,0x20,
    0x10,0x00,0x00,0x00,0x70,0xf0,0x70,0x78,0x70,0x70,0x78,0xf0,0x60,0x18,0x48,0x20,0xf0,0xf0,0x70,0xf0,
    0x78,0xb8,0x78,0x70,0x88,0x88,0x88,0x88,0x88,0xf8,0x20,0x20,0x10,0x00,0x18,0x20,0x00,0x50,0xa0,0x10,
    0x20,0x00,0x40,0x10,0x20,0x20,0x00,0x00,0x00,0x10,0xa8,0x20,0x08,0x30,0x48,0xf0,0xf0,0x10,0x70,0x88,
    0x20,0x20,0x20,0x00,0x10,0x10,0xa8,0x88,0xf0,0x80,0x88,0xf0,0xf0,0x80,0xf8,0x20,0x10,0xc0,0x80,0xa8,
    0xa8,0x88,0x88,0x88,0x88,0x70,0x20,0x88,0x50,0x88,0x20,0x50,0x20,0x40,0x20,0x10,0x00,0x00,0x00,0x08,
    0x88,0x88,0x88,0x88,0x20,0x88,0x88,0x20,0x08,0x50,0x20,0xa8,0x88,0x88,0x88,0x88,0xc0,0x80,0x20,0x88,
    0x88,0x88,0x50,0x88,0x10,0x40,0x20,0x08,0x00,0xd8,0x20,0x00,0x50,0x70,0x20,0x68,0x00,0x40,0x10,0xf8,
    0xf8,0x00,0xf8,0x00,0x20,0xc8,0x20,0x10,0x08,0x88,0x08,0x88,0x10,0x88,0x78,0x00,0x00,0x40,0x00,0x08,
    0x20,0xa8,0xf8,0x88,0x80,0x88,0x80,0x80,0xb8,0x88,0x20,0x10,0xc0,0x80,0x88,0x98,0x88,0xf0,0x88,0xf0,
    0x08,0x20,0x88,0x50,0xa8,0x20,0x20,0x40,0x40,0x10,0x10,0x00,0x00,0x00,0x78,0x88,0x80,0x88,0xf8,0x20,
    0x88,0x88,0x20,0x08,0x60,0x20,0xa8,0x88,0x88,0x88,0x88,0x80,0x70,0x20,0x88,0x50,0xa8,0x20,0x88,0x20,
    0x20,0x20,0x10,0x00,0xf0,0x00,0x00,0xf8,0x28,0x28,0x90,0x00,0x40,0x10,0x20,0x20,0x00,0x00,0x00,0x20,
    0x88,0x20,0x20,0x08,0xf8,0x08,0x88,0x20,0x88,0x08,0x00,0x00,0x20,0xf8,0x10,0x00,0x98,0x88,0x88,0x80,
    0x88,0x80,0x80,0x88,0x88,0x20,0x90,0xa0,0x80,0x88,0x88,0x88,0x80,0x88,0xa0,0x08,0x20,0x88,0x50,0xa8,
    0x50,0x20,0x80,0x40,0x10,0x10,0x00,0x00,0x00,0x88,0x88,0x80,0x88,0x80,0x20,0x88,0x88,0x20,0x08,0x60,
    0x20,0xa8,0x88,0x88,0x88,0x88,0x80,0x08,0x20,0x88,0x50,0xa8,0x20,0x88,0x40,0x20,0x20,0x10,0x00,0x70,
    0x20,0x00,0x50,0xa8,0x54,0x90,0x00,0x20,0x20,0x50,0x20,0x20,0x00,0x20,0x40,0x88,0x20,0x40,0x88,0x08,
    0x88,0x88,0x20,0x88,0x08,0x20,0x20,0x10,0x00,0x20,0x20,0x80,0x88,0x88,0x88,0x90,0x80,0x80,0x88,0x88,
    0x20,0x90,0x90,0x80,0x88,0x88,0x88,0x80,0xa8,0x90,0x88,0x20,0x88,0x20,0xd8,0x88,0x20,0x80,0x40,0x08,
    0x10,0x00,0x00,0x00,0x88,0x88,0x88,0x88,0x80,0x20,0x88,0x88,0x20,0x08,0x50,0x20,0xa8,0x88,0x88,0x88,
    0x88,0x80,0x08,0x20,0x88,0x20,0xa8,0x50,0x88,0x80,0x20,0x20,0x10,0x00,0x60,0x20,0x00,0x50,0x70,0x48,
    0x68,0x00,0x10,0x40,0x00,0x00,0x20,0x00,0x20,0x40,0x70,0x70,0xf8,0x70,0x08,0x70,0x70,0x20,0x70,0x70,
    0x20,0x20,0x08,0x00,0x40,0x20,0x78,0x88,0xf0,0x70,0xe0,0xf8,0x80,0x70,0x88,0x70,0x60,0x88,0xf8,0x88,
    0x88,0x70,0x80,0x70,0x88,0x70,0x20,0x70,0x20,0x88,0x88,0x20,0xf8,0x70,0x08,0x70,0x00,0x00,0x00,0x78,
    0xf0,0x70,0x78,0x78,0x20,0x78,0x88,0x70,0x08,0x48,0x70,0xa8,0x88,0x70,0xf0,0x78,0x80,0xf0,0x18,0x78,
    0x20,0x70,0x88,0x78,0xf8,0x18,0x20,0x60,0x00,0x60,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x08,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x00,0x80,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x30,0x00,
    0x00,0x00,0x00,0x00,0x80,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,
};

}
