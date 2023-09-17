#include <gtest/gtest.h>
#include "libde265/bitstream.h"

TEST(bitstream, get_bits)
{
    // GIVEN a 32 bit value
    std::vector<uint8_t> data { 0xCA, 0xFE, 0xBA, 0xBE };
    // WHEN bitreader reads bits
    bitreader br;
    bitreader_init(&br, data.data(), data.size());
    // THEN the bits are returned in the correct order
    ASSERT_EQ(0xC, get_bits(&br,4));
    ASSERT_EQ(0xA, get_bits(&br,4));
    ASSERT_EQ(0xF, get_bits(&br,4));
    ASSERT_EQ(0xE, get_bits(&br,4));
    ASSERT_EQ(0xB, get_bits(&br,4));
    ASSERT_EQ(0xA, get_bits(&br,4));
    ASSERT_EQ(0xB, get_bits(&br,4));
    ASSERT_EQ(0xE, get_bits(&br,4));
}

TEST(bitstream, get_bits_fast)
{
    // GIVEN a 32 bit value
    std::vector<uint8_t> data { 0xCA, 0xFE, 0xBA, 0xBE };
    // WHEN bitreader reads bits
    bitreader br;
    bitreader_init(&br, data.data(), data.size());
    // THEN the bits are returned in the correct order
    ASSERT_EQ(0xC, get_bits_fast(&br,4));
    ASSERT_EQ(0xA, get_bits_fast(&br,4));
    ASSERT_EQ(0xF, get_bits_fast(&br,4));
    ASSERT_EQ(0xE, get_bits_fast(&br,4));
    ASSERT_EQ(0xB, get_bits_fast(&br,4));
    ASSERT_EQ(0xA, get_bits_fast(&br,4));
    ASSERT_EQ(0xB, get_bits_fast(&br,4));
    ASSERT_EQ(0xE, get_bits_fast(&br,4));
}

TEST(bitstream, skip_bits)
{
   // GIVEN a 32 bit value
    std::vector<uint8_t> data { 0xCA, 0xFE, 0xBA, 0xBE };
    // WHEN bitreader skips bits
    bitreader br;
    bitreader_init(&br, data.data(), data.size());
    skip_bits(&br, 16);
    // THEN correct value is returned
    ASSERT_EQ(0xBA, get_bits(&br,8));
}

TEST(bitstream, skip_bits_fast)
{
   // GIVEN a 32 bit value
    std::vector<uint8_t> data { 0xCA, 0xFE, 0xBA, 0xBE };
    // WHEN bitreader skips bits
    bitreader br;
    bitreader_init(&br, data.data(), data.size());
    skip_bits_fast(&br, 16);
    // THEN correct value is returned
    ASSERT_EQ(0xBA, get_bits(&br,8));
}

TEST(bitstream, skip_to_byte_boundary)
{
   // GIVEN a 32 bit value
    std::vector<uint8_t> data { 0xCA, 0xFE, 0xBA, 0xBE };
    // WHEN bitreader skips bits
    bitreader br;
    bitreader_init(&br, data.data(), data.size());
    skip_bits_fast(&br, 17);
    skip_to_byte_boundary(&br);
    // THEN correct value is returned
    ASSERT_EQ(0xBE, get_bits(&br,8));
}

TEST(bitstream, check_rbsp_trailing_bits)
{
    {
        std::vector<uint8_t> data { 0x81 };
        bitreader br;
        bitreader_init(&br, data.data(), data.size());
        ASSERT_FALSE(check_rbsp_trailing_bits(&br));
    }

    {
        std::vector<uint8_t> data { 0x80 };
        bitreader br;
        bitreader_init(&br, data.data(), data.size());
        ASSERT_TRUE(check_rbsp_trailing_bits(&br));
    }
}