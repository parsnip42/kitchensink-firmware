#ifndef INCLUDED_FONT_H
#define INCLUDED_FONT_H

#include "types/strref.h"
#include <cstdint>

namespace Font
{

// constexpr int kWidth     = 8;
// constexpr int kHeight    = 14;
constexpr int kWidth     = 6;
constexpr int kHeight    = 12;

constexpr int kBpp       = 1;
constexpr int kCharCount = 95;

extern const uint8_t fontData[];

inline
constexpr int width(const StrRef& text)
{
    return text.length() * kWidth;
}

}

#endif
