#include "gtest/gtest.h"

#include "types/dataref.h"
#include "crypto/entropypool.h"
#include "config.h"

#include <algorithm>
#include <ostream>

static void PrintTo(const DataRef& dataRef,
             std::ostream*  os)
{
    *os << "Size=" << dataRef.size() << " ";
    
    for (auto d : dataRef)
    {
        *os << (int)d << " ";
    }
}

TEST(EntropyPool, Default)
{
    EntropyPool ep;

    ASSERT_EQ(ep.count(), 0);
    ASSERT_EQ(ep.entryCount(), 0);
    ASSERT_EQ(ep.begin(), ep.end());
}

TEST(EntropyPool, InsertClear)
{
    EntropyPool ep;

    ep.insert(0xff);
    
    ASSERT_EQ(ep.count(), 1);
    ASSERT_EQ(ep.entryCount(), 0);
    ASSERT_NE(ep.begin(), ep.end());

    ep.clear();
    
    ASSERT_EQ(ep.count(), 0);
    ASSERT_EQ(ep.entryCount(), 0);
    ASSERT_EQ(ep.begin(), ep.end());
}

TEST(EntropyPool, Simple)
{
    // For hardwired SHA256 values.
    ASSERT_EQ(Config::kEntropySourceFactor, 2);

    // Hack to forcibly zero initialise underlying memory. This is only
    // necessary for testing.
    char epData[sizeof(EntropyPool)];

    std::fill(epData, epData + sizeof(epData), 0);
    
    EntropyPool* epPtr(new (epData) EntropyPool());
    EntropyPool& ep(*epPtr);

    for (std::size_t i(0); i < 32 * Config::kEntropySourceFactor; i+=4)
    {
        ep.insert('A');
        ep.insert('B');
        ep.insert('C');
        ep.insert('D');
    }

    ASSERT_EQ(ep.count(), 32 * Config::kEntropySourceFactor);
    ASSERT_EQ(ep.entryCount(), 1);    
    
    std::array<uint8_t, 32> output;

    ASSERT_TRUE(ep.read(output));
    ASSERT_EQ(ep.count(), 0);
    ASSERT_EQ(ep.entryCount(), 0);

    DataRef outputRef(output);

    // printf 'ABCD%.0s' {1..16} | sha256sum
    const uint8_t expected[] =
    {
        0x6b, 0xf3, 0xf1, 0xe7, 0x14, 0xbb, 0x3a, 0xd1,
        0x49, 0x5e, 0xd7, 0x43, 0xcc, 0x67, 0x96, 0xdb,
        0x84, 0x50, 0xff, 0x25, 0x5d, 0x47, 0x9d, 0x6a,
        0xfb, 0x21, 0x80, 0xd9, 0xc3, 0xc3, 0xd4, 0xbc
    };

    DataRef expectedRef(expected, expected + sizeof(expected));

    ASSERT_EQ(outputRef, expectedRef);
}

TEST(EntropyPool, Overflow)
{
    ASSERT_EQ(Config::kEntropySourceFactor, 2);

    char epData[sizeof(EntropyPool)];

    std::fill(epData, epData + sizeof(epData), 0);
    
    EntropyPool* epPtr(new (epData) EntropyPool());
    EntropyPool& ep(*epPtr);

    for (std::size_t i(0); i < Config::kEntropyPoolSize; ++i)
    {
        ep.insert('A');
    }

    for (std::size_t i(0); i < 32 * Config::kEntropySourceFactor; ++i)
    {
        ep.insert('Z');
    }

    ASSERT_EQ(ep.count(), Config::kEntropyPoolSize + (32 * Config::kEntropySourceFactor));
    
    std::array<uint8_t, 32> output;

    ASSERT_TRUE(ep.read(output));
    ASSERT_EQ(ep.count(), Config::kEntropyPoolSize - (32 * Config::kEntropySourceFactor));

    {
        DataRef outputRef(output);

        // printf '\x1b%.0s' {1..100} | sha256sum
        const uint8_t expected[] =
        {
            0xc2, 0xe7, 0x87, 0x8c, 0xaa, 0x52, 0x81, 0x65,
            0x5c, 0xfb, 0x83, 0xe4, 0x13, 0xc4, 0x3b, 0x82,
            0x0a, 0x70, 0x73, 0x00, 0x0d, 0x7f, 0x08, 0xeb,
            0x04, 0x76, 0x35, 0xff, 0xf4, 0x4a, 0x2a, 0x79
        };
    
        DataRef expectedRef(expected, expected + sizeof(expected));

        ASSERT_EQ(outputRef, expectedRef);
    }
    
    ASSERT_TRUE(ep.read(output));
    ASSERT_EQ(ep.count(), Config::kEntropyPoolSize - (64 * Config::kEntropySourceFactor));

    {
        DataRef outputRef(output);

        // printf 'A%.0s' {1..100} | sha256sum
        const uint8_t expected[] =
        {
            0xd5, 0x3e, 0xda, 0x7a, 0x63, 0x7c, 0x99, 0xcc,
            0x7f, 0xb5, 0x66, 0xd9, 0x6e, 0x9f, 0xa1, 0x09,
            0xbf, 0x15, 0xc4, 0x78, 0x41, 0x0a, 0x3f, 0x5e,
            0xb4, 0xd4, 0xc4, 0xe2, 0x6c, 0xd0, 0x81, 0xf6
        };
    
        DataRef expectedRef(expected, expected + sizeof(expected));

        ASSERT_EQ(outputRef, expectedRef);
    }
}
