#ifndef INCLUDED_RENDERUTIL_H
#define INCLUDED_RENDERUTIL_H

#include "ui/rasterline.h"

class StrRef;

namespace RenderUtil
{

int fill(const RasterLine& row, uint8_t color);
int render(const StrRef& text, int x, int line, const RasterLine& row, uint8_t fg = 0xf, uint8_t bg = 0x0);

};

#endif
