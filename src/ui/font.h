#ifndef INCLUDED_FONT_H
#define INCLUDED_FONT_H

#include <cstdint>

namespace Font
{

constexpr int kWidth = 8;
constexpr int kHeight = 14;
constexpr int kCharCount = 95;

extern const uint8_t fontData[];

}

#endif
