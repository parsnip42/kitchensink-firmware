#include "ui/renderutil.h"

#include "types/strref.h"

namespace RenderUtil
{

int fill(const RasterLine& row, uint8_t color)
{
    // TODO: Optimise to std::memset()
    for (std::size_t i(0); i < row.size(); ++i)
    {
        row[i] = color;
    }

    return row.size();
}

int text(const StrRef& str, int x, int line, const RasterLine& row, uint8_t fg, uint8_t bg)
{
    auto len(std::min<int>(row.size(), Font::width(str)));
    
    if (line >= 0 && line < Font::kHeight)
    {
        for (const auto chr : str)
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
    else
    {
        fill(row.subset(x, len), bg);
    }
    
    return len;
}

int textPrefix(const StrRef& prefix, const StrRef& str, int x, int line, const RasterLine& row, uint8_t prefixFg, uint8_t prefixBg, uint8_t fg, uint8_t bg)
{
    if (!str.beginsWithCase(prefix))
    {
        return text(str, x, line, row, fg, bg);
    }
    else
    {
        auto prefixLen(text(str.substr(0, prefix.length()), x, line, row, prefixFg, prefixBg));
        
        return prefixLen + text(str.substr(prefix.length()), x + prefixLen, line, row, fg, bg);
    }
}

}
