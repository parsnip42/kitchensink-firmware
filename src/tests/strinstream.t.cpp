#include "gtest/gtest.h"

#include "types/datarefinstream.h"
#include "types/strbuf.h"
#include "types/strinstream.h"
#include "types/stroutstream.h"

TEST(StrInStream, Default)
{
    const char* TestStr = "ABC\nDEF\n\nGHI";

    DataRefInStream is(TestStr);
    StrInStream sis(is);

    {
        StrBuf<12> str;

        ASSERT_TRUE(sis.readLine(str));
        ASSERT_EQ(str, "ABC");
    }

    {
        StrBuf<12> str;

        ASSERT_TRUE(sis.readLine(str));
        ASSERT_EQ(str, "DEF");
    }
    
    {
        StrBuf<12> str;

        ASSERT_TRUE(sis.readLine(str));
        ASSERT_EQ(str, "");
    }

    {
        StrBuf<12> str;

        ASSERT_TRUE(sis.readLine(str));
        ASSERT_EQ(str, "GHI");
    }

    {
        StrBuf<12> str;

        ASSERT_FALSE(sis.readLine(str));
    }
}










