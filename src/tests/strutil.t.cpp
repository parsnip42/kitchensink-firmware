#include "gtest/gtest.h"

#include "types/strref.h"
#include "types/strutil.h"

TEST(StrUtil, NextToken)
{
    StrRef data(" A BB CCC ");
    
    auto token(StrUtil::nextToken(data, " "));

    ASSERT_EQ(token, "A");
    
    token = StrUtil::nextToken(data, " ", token);

    ASSERT_EQ(token, "BB");
    
    token = StrUtil::nextToken(data, " ", token);

    ASSERT_EQ(token, "CCC");
    
    token = StrUtil::nextToken(data, " ", token);

    ASSERT_TRUE(token.empty());
}
