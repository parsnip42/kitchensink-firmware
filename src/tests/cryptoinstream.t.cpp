#include "gtest/gtest.h"

#include "types/datarefinstream.h"
#include "types/arrayoutstream.h"
#include "crypto/cryptoinstream.h"

#include <array>

TEST(CryptoInStream, Simple)
{
    const uint8_t AesFile[] =
    {
        0x41, 0x45, 0x53, 0x02, 0x00, 0x00, 0x19, 0x43, 0x52, 0x45, 0x41, 0x54, 0x45, 0x44, 0x5f, 0x42,
        0x59, 0x00, 0x70, 0x79, 0x41, 0x65, 0x73, 0x43, 0x72, 0x79, 0x70, 0x74, 0x20, 0x30, 0x2e, 0x33,
        0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xb3, 0x1f, 0x6c, 0xe9, 0x00, 0xa9, 0x36, 0x9f, 0x12, 0xf5, 0x75, 0x0e,
        0x37, 0xef, 0x17, 0xaa, 0x5a, 0x29, 0xfe, 0xb5, 0x7a, 0x1b, 0x92, 0xea, 0x08, 0xae, 0x92, 0x35,
        0xa2, 0xc7, 0x8d, 0x55, 0x13, 0x6a, 0x5d, 0x7f, 0xcc, 0x28, 0x74, 0x3f, 0x8c, 0x05, 0x0e, 0x45,
        0xd4, 0xc7, 0x94, 0x29, 0x65, 0xc7, 0x29, 0xc7, 0xc5, 0x20, 0xef, 0x51, 0xe7, 0x64, 0x57, 0x59,
        0x23, 0x21, 0xc6, 0x7c, 0xdf, 0x2a, 0xb7, 0x08, 0xf5, 0x1e, 0xef, 0xa9, 0x49, 0x55, 0xc7, 0xff,
        0x4d, 0xb0, 0x98, 0x0d, 0x53, 0xf8, 0x69, 0xd6, 0x71, 0x07, 0x25, 0xe7, 0xd2, 0xec, 0x02, 0x4e,
        0x80, 0x40, 0xd8, 0x86, 0x4d, 0xf4, 0xf7, 0xfc, 0xde, 0xc0, 0x15, 0xac, 0xea, 0x56, 0xfc, 0x82,
        0x1f, 0x85, 0x3e, 0x32, 0x0f, 0x0b, 0x44, 0xd4, 0x35, 0xa7, 0x87, 0xd3, 0x7b, 0xda, 0x06, 0xda,
        0x5b, 0xa9, 0x3e, 0x9c, 0xd1, 0x9c, 0xfc, 0x35, 0x3d, 0xbb, 0x89, 0xaa, 0xa7, 0xbc, 0x0d, 0x3a,
        0x41, 0x75, 0x43, 0xbd, 0xfd
    };
    
    DataRefInStream is(DataRef(AesFile, AesFile + sizeof(AesFile)));
    CryptoInStream cis(is, "test");

    // FIXME: Incorporate password suffix.

    // ASSERT_EQ(cis.error(), CryptoInStream::Error::kNone);

    std::array<uint8_t, 100> output;

    output.fill(0);
    
    ArrayOutStream out(output);

    DataRef expected("This is a test\n");

    // ASSERT_EQ(cis.read(out, out.remaining()), expected.size());
    // ASSERT_EQ(out.data(), expected);
}










