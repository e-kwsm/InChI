#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichiprt2.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
}

TEST(test_ichiprt2, MakeStereoString_outputs_expected_sp3_string)
{
    // Prepare input arrays for 8 stereo centers
    AT_NUMB at1[8] = {3,4,5,6,7,8,9,10};
    S_CHAR parity[8] = {1,1,2,2,1,2,2,1};

    // Prepare strbuf (empty)
    INCHI_IOS_STRING strbuf = {0};

    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    // Call MakeStereoString
    int bOverflow = 0;
    int ret = MakeStereoString(at1, nullptr, parity, 0, 8, &strbuf, 0, &bOverflow);

    // Check that strbuf contains the expected substring
    EXPECT_EQ(strbuf.nUsedLength, strlen(strbuf.pStr));
    EXPECT_NE(std::string(strbuf.pStr).find("3-,4-,5+,6+,7-,8+,9+,10-"), std::string::npos);
    EXPECT_EQ(strbuf.pStr[0], '3'); // Should start with 3-
    EXPECT_EQ(bOverflow, 0);
    EXPECT_EQ(ret, 24);

    inchi_strbuf_close(&strbuf);
}

TEST(test_ichiprt2, MakeMult_mult_gt_1_appends_number_and_delim)
{
    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    int bOverflow = 0;
    int ret = MakeMult(5, "-", &strbuf, 0, &bOverflow);

    EXPECT_EQ(std::string(strbuf.pStr), "5-");
    EXPECT_EQ(ret, 2); // "3-".length() == 2, but MakeMult returns n (number of chars written)
    EXPECT_EQ(bOverflow, 0);

    inchi_strbuf_close(&strbuf);
}

TEST(test_ichiprt2, MakeMult_mult_eq_1_does_nothing)
{
    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);
    inchi_strbuf_printf(&strbuf, "start");

    int bOverflow = 0;
    int ret = MakeMult(1, "-", &strbuf, 0, &bOverflow);

    EXPECT_EQ(std::string(strbuf.pStr), "start");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(bOverflow, 0);

    inchi_strbuf_close(&strbuf);
}
