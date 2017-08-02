#include "ui/renderutil.h"

#include "types/strref.h"

namespace RenderUtil
{

void render(const StrRef& text, int x, int line, const RasterLine& row, uint8_t fg, uint8_t bg)
{
    if (line >= 0 && line <  Font::kHeight)
    {
        for (const auto chr : text)
        {
            uint8_t data(0xff);
            
            if (chr > 32 && chr <= 32 + Font::kCharCount)
            {
                data = Font::fontData[chr - 33 + (line * Font::kCharCount)];
            }
            else if (chr == 32)
            {
                data = 0;
            }

            for (int w(0); x < (int)row.size() && w < Font::kWidth; ++w)
            {
                if (x >= 0)
                {
                    row[x++] = ((data >> (7 - w)) & 1) ? fg : bg;
                }
            }
        }
    }
}

}
