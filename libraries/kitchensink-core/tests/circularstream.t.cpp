#include "gtest/gtest.h"

#include "types/arrayoutstream.h"
#include "types/circularstream.h"

TEST(CircularStream, Default)
{
    CircularStream<5> cs;

    ASSERT_TRUE(cs.empty());
    ASSERT_EQ(cs.size(), 0);
}

TEST(CircularStream, Simple)
{
    CircularStream<48> cs;

    const uint8_t TestDataRaw[] =
    {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15
    };
    
    DataRef testData(TestDataRaw, TestDataRaw + sizeof(TestDataRaw));

    ASSERT_EQ(cs.write(testData), testData.size());

    ASSERT_FALSE(cs.empty());
    ASSERT_EQ(cs.size(), testData.size());

    std::array<uint8_t, 48> outData;
    ArrayOutStream outStream(outData);

    ASSERT_EQ(cs.read(outStream, outData.size()), testData.size());

    ASSERT_EQ(testData, DataRef(outData.begin(), outData.begin() + testData.size()));

    ASSERT_TRUE(cs.empty());
    ASSERT_EQ(cs.size(), 0);
}

TEST(CircularStream, Rotating)
{
    const uint8_t TestDataRaw[] =
    {
        0, 1, 2
    };
    
    DataRef testData(TestDataRaw, TestDataRaw + sizeof(TestDataRaw));

    CircularStream<13> cs;

    std::array<uint8_t, 48> outData;
    ArrayOutStream outStream(outData);

    for (int i = 0; i < 1000; ++i)
    {
        ASSERT_EQ(cs.write(testData), testData.size());
        ASSERT_FALSE(cs.empty());
        ASSERT_EQ(cs.size(), testData.size());

        ASSERT_EQ(cs.read(outStream, outData.size()), testData.size());

        ASSERT_EQ(testData, DataRef(outData.begin(), outData.begin() + testData.size()));
            
        ASSERT_TRUE(cs.empty());
        ASSERT_EQ(cs.size(), 0);
    }
}

TEST(CircularStream, Overflow)
{
    CircularStream<13> cs;

    const uint8_t TestDataRaw[] =
    {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15
    };
    
    DataRef testData(TestDataRaw, TestDataRaw + sizeof(TestDataRaw));

    ASSERT_EQ(cs.write(testData), 13);

    ASSERT_FALSE(cs.empty());
    ASSERT_EQ(cs.size(), 13);

    std::array<uint8_t, 48> outData;
    ArrayOutStream outStream(outData);

    ASSERT_EQ(cs.read(outStream, outData.size()), 13);

    DataRef testDataTruncated(TestDataRaw, TestDataRaw + 13);
    
    ASSERT_EQ(testDataTruncated, DataRef(outData.begin(), outData.begin() + 13));

    ASSERT_TRUE(cs.empty());
    ASSERT_EQ(cs.size(), 0);    
}
