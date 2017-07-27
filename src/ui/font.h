#ifndef INCLUDED_FONT_H
#define INCLUDED_FONT_H

#include <cstdint>

namespace Font
{

constexpr int kWidth = 6;
constexpr int kHeight = 12;
constexpr int kBpp = 4;
constexpr int kCharCount = 95;

extern const uint8_t fontData[];

}

#endif
