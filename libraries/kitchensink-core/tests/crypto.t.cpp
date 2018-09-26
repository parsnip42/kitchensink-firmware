#include "gtest/gtest.h"

#include "types/arrayoutstream.h"
#include "types/datarefinstream.h"
#include "types/dataref.h"
#include "types/strref.h"
#include "crypto/cryptoinstream.h"
#include "crypto/cryptooutstream.h"
#include "crypto/entropypool.h"

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

namespace
{
// D(key, E(key, data)) = data
void sanityCheck(const DataRef& testData,
                 const StrRef&  password,
                 int            prngSeed)
{
    EntropyPool entropyPool;

    // rand() is a PRNG so don't even think about doing this in real code!
    srand(prngSeed);
    
    for (int i(0); i < 10000; ++i)
    {
        entropyPool.insert(uint8_t(rand() & 0xff));
    }

    std::array<uint8_t, 1024 * 1024> encryptedData;
    ArrayOutStream encryptedOut(encryptedData);

    {
        CryptoOutStream cryptOut(encryptedOut, password, entropyPool);

        cryptOut.write(testData);
    }

    ASSERT_GT(encryptedOut.position(), testData.size());

    DataRefInStream encryptedIn(encryptedOut.data());
    
    CryptoInStream cryptIn(encryptedIn, password);
    
    ASSERT_EQ(cryptIn.error(), CryptoInStream::Error::kNone);
    
    std::array<uint8_t, 1024 * 1024> decryptedData;
    ArrayOutStream decryptedOut(decryptedData);

    std::size_t size(0);
    
    while (true)
    {
        auto read(cryptIn.read(decryptedOut, decryptedOut.remaining()));

        if (read == 0)
        {
            break;
        }
        
        size += read;
    }

    ASSERT_EQ(testData.size(), size);
    ASSERT_EQ(decryptedOut.data(), testData);
}

}

TEST(Crypto, Sanity0)
{
    const uint8_t TestDataRaw[] =
    {
        0, 1, 2, 3
    };
    
    DataRef testData(TestDataRaw, TestDataRaw + sizeof(TestDataRaw));
    StrRef password("test");
    
    sanityCheck(testData, password, 0);
}

TEST(Crypto, Sanity1)
{
    const uint8_t TestDataRaw[] =
    {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15
    };
    
    DataRef testData(TestDataRaw, TestDataRaw + sizeof(TestDataRaw));
    StrRef password("password!123");
    
    sanityCheck(testData, password, 123);
}

TEST(Crypto, Sanity2)
{
    const uint8_t TestDataRaw[] =
    {
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x00,0x00,
        0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x20,0x50,0x50,0x20,0x48,0x20,0x20,0x10,0x40,0x00,
        0x00,0x00,0x00,0x00,0x08,0x70,0x20,0x70,0x70,0x08,0xf8,0x70,0xf8,0x70,0x70,0x00,0x00,0x00,0x00,0x00,
        0x70,0x70,0x70,0xf0,0x70,0xe0,0xf8,0xf8,0x70,0x88,0x70,0x38,0x88,0x80,0x88,0x88,0x70,0xf0,0x70,0xf0,
        0x70,0xf8,0x88,0x88,0x88,0x88,0x88,0xf8,0x70,0x40,0x70,0x50,0x00,0x00,0x00,0x80,0x00,0x08,0x00,0x18,
        0x00,0x80,0x20,0x08,0x40,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
        0x18,0x20,0x60,0xa8,0x0c,0x20,0x50,0x50,0x70,0xa8,0x50,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x08,
        0x88,0x60,0x88,0x88,0x18,0x80,0x80,0x08,0x88,0x88,0x00,0x00,0x08,0x00,0x40,0x88,0x88,0x88,0x88,0x88,
        0x90,0x80,0x80,0x88,0x88,0x20,0x10,0x90,0x80,0xd8,0x88,0x88,0x88,0x88,0x88,0x88,0x20,0x88,0x88,0x88,
        0x88,0x88,0x08,0x40,0x40,0x10,0x88,0x00,0x00,0x00,0x80,0x00,0x08,0x00,0x20,0x00,0x80,0x00,0x00,0x40,
        0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x10,0x90,0x0c,
        0x20,0x00,0xf8,0xa8,0x50,0x50,0x00,0x40,0x10,0x50,0x20,0x00,0x00,0x00,0x10,0x98,0x20,0x88,0x08,0x28,
        0x80,0x80,0x08,0x88,0x88,0x20,0x20,0x10,0xf8,0x20,0x88,0x98,0x88,0x88,0x80,0x88,0x80,0x80,0x80,0x88,
        0x20,0x10,0xa0,0x80,0xa8,0xc8,0x88,0x88,0x88,0x88,0x80,0x20,0x88,0x88,0x88,0x50,0x50,0x10,0x40,0x20,
        0x10,0x00,0x00,0x00,0x70,0xf0,0x70,0x78,0x70,0x70,0x78,0xf0,0x60,0x18,0x48,0x20,0xf0,0xf0,0x70,0xf0,
        0x78,0xb8,0x78,0x70,0x88,0x88,0x88,0x88,0x88,0xf8,0x20,0x20,0x10,0x00,0x18,0x20,0x00,0x50,0xa0,0x10,
        0x20,0x00,0x40,0x10,0x20,0x20,0x00,0x00,0x00,0x10,0xa8,0x20,0x08,0x30,0x48,0xf0,0xf0,0x10,0x70,0x88,
        0x20,0x20,0x20,0x00,0x10,0x10,0xa8,0x88,0xf0,0x80,0x88,0xf0,0xf0,0x80,0xf8,0x20,0x10,0xc0,0x80,0xa8,
        0xa8,0x88,0x88,0x88,0x88,0x70,0x20,0x88,0x50,0x88,0x20,0x50,0x20,0x40,0x20,0x10,0x00,0x00,0x00,0x08,
        0x88,0x88,0x88,0x88,0x20,0x88,0x88,0x20,0x08,0x50,0x20,0xa8,0x88,0x88,0x88,0x88,0xc0,0x80,0x20,0x88,
        0x88,0x88,0x50,0x88,0x10,0x40,0x20,0x08,0x00,0xd8,0x20,0x00,0x50,0x70,0x20,0x68,0x00,0x40,0x10,0xf8,
        0xf8,0x00,0xf8,0x00,0x20,0xc8,0x20,0x10,0x08,0x88,0x08,0x88,0x10,0x88,0x78,0x00,0x00,0x40,0x00,0x08,
        0x20,0xa8,0xf8,0x88,0x80,0x88,0x80,0x80,0xb8,0x88,0x20,0x10,0xc0,0x80,0x88,0x98,0x88,0xf0,0x88,0xf0,
        0x08,0x20,0x88,0x50,0xa8,0x20,0x20,0x40,0x40,0x10,0x10,0x00,0x00,0x00,0x78,0x88,0x80,0x88,0xf8,0x20,
        0x88,0x88,0x20,0x08,0x60,0x20,0xa8,0x88,0x88,0x88,0x88,0x80,0x70,0x20,0x88,0x50,0xa8,0x20,0x88,0x20,
        0x20,0x20,0x10,0x00,0xf0,0x00,0x00,0xf8,0x28,0x28,0x90,0x00,0x40,0x10,0x20,0x20,0x00,0x00,0x00,0x20,
        0x88,0x20,0x20,0x08,0xf8,0x08,0x88,0x20,0x88,0x08,0x00,0x00,0x20,0xf8,0x10,0x00,0x98,0x88,0x88,0x80,
        0x88,0x80,0x80,0x88,0x88,0x20,0x90,0xa0,0x80,0x88,0x88,0x88,0x80,0x88,0xa0,0x08,0x20,0x88,0x50,0xa8,
        0x50,0x20,0x80,0x40,0x10,0x10,0x00,0x00,0x00,0x88,0x88,0x80,0x88,0x80,0x20,0x88,0x88,0x20,0x08,0x60,
        0x20,0xa8,0x88,0x88,0x88,0x88,0x80,0x08,0x20,0x88,0x50,0xa8,0x20,0x88,0x40,0x20,0x20,0x10,0x00,0x70,
        0x20,0x00,0x50,0xa8,0x54,0x90,0x00,0x20,0x20,0x50,0x20,0x20,0x00,0x20,0x40,0x88,0x20,0x40,0x88,0x08,
        0x88,0x88,0x20,0x88,0x08,0x20,0x20,0x10,0x00,0x20,0x20,0x80,0x88,0x88,0x88,0x90,0x80,0x80,0x88,0x88,
        0x20,0x90,0x90,0x80,0x88,0x88,0x88,0x80,0xa8,0x90,0x88,0x20,0x88,0x20,0xd8,0x88,0x20,0x80,0x40,0x08,
        0x10,0x00,0x00,0x00,0x88,0x88,0x88,0x88,0x80,0x20,0x88,0x88,0x20,0x08,0x50,0x20,0xa8,0x88,0x88,0x88,
        0x88,0x80,0x08,0x20,0x88,0x20,0xa8,0x50,0x88,0x80,0x20,0x20,0x10,0x00,0x60,0x20,0x00,0x50,0x70,0x48,
        0x68,0x00,0x10,0x40,0x00,0x00,0x20,0x00,0x20,0x40,0x70,0x70,0xf8,0x70,0x08,0x70,0x70,0x20,0x70,0x70,
        0x20,0x20,0x08,0x00,0x40,0x20,0x78,0x88,0xf0,0x70,0xe0,0xf8,0x80,0x70,0x88,0x70,0x60,0x88,0xf8,0x88,
        0x88,0x70,0x80,0x70,0x88,0x70,0x20,0x70,0x20,0x88,0x88,0x20,0xf8,0x70,0x08,0x70,0x00,0x00,0x00,0x78,
        0xf0,0x70,0x78,0x78,0x20,0x78,0x88,0x70,0x08,0x48,0x70,0xa8,0x88,0x70,0xf0,0x78,0x80,0xf0,0x18,0x78,
        0x20,0x70,0x88,0x78,0xf8,0x18,0x20,0x60,0x00,0x60,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x08,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x00,0x80,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x30,0x00,
        0x00,0x00,0x00,0x00,0x80,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,
    };

    DataRef testData(TestDataRaw, TestDataRaw + sizeof(TestDataRaw));
    StrRef password("The quick brown fox jumps over the lazy dog");
    sanityCheck(testData, password, 456);
}

TEST(Crypto, Sanity3)
{
     // Prime to avoid matching any block size.
    static const size_t HugeSize = 524287;
    
    uint8_t* testDataRaw = new uint8_t[HugeSize];

    srand(123);
    
    for (size_t i = 0; i < HugeSize; ++i)
    {
        testDataRaw[i] = rand() & 0xff;
    }
    
    DataRef testData(testDataRaw, testDataRaw + HugeSize);
    StrRef password("Another password!123");
    sanityCheck(testData, password, 789);
}
