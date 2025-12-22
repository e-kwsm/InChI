#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>
#include <vector>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichiprt1.c"
}


TEST(test_ichiprt1, test_OutputINCHI_StereoLayer)
{

    // Prepare minimal dummy arguments
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};
    char lf[] = "\n";
    char tab[] = "\t";

    // Initialize string buffer (simulate allocation)
    // inchi_strbuf_init(&strbuf, 128, 128);
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    // int OutputINCHI_StereoLayer( CANON_GLOBALS    *pCG,
    //                             INCHI_IOSTREAM   *out_file,
    //                             INCHI_IOS_STRING *strbuf,
    //                             INCHI_OUT_CTL    *io,
    //                             char             *pLF,
    //                             char             *pTAB )

    // Call the function under test
    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, lf, tab);

    // Check that the function returns 0 (success) or expected error code
    // (You may need to adjust this depending on the actual implementation)
    EXPECT_EQ(ret, 0);

    // Clean up
    inchi_strbuf_close(&strbuf);

}

TEST(test_ichiprt1, OutputINCHI_StereoLayer_s1)
{
    // Prepare minimal input structures
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};

    // Set up io to trigger the /s (stereo type) segment
    io.sDifSegs[0][DIFS_s_STYPE] = DIFV_OUTPUT_FILL_T; // nonzero triggers INChI_SegmentAction


    io.nCurINChISegment = 0;
    io.iCurTautMode = 0;
    io.bPlainTextTags = 1;
    io.bRelativeStereo[0] = 0;
    io.bRacemicStereo[0] = 0;
    io.bAlways = 0;
    io.nTag = 2; // plain text
    io.bTag1 = IL_STER;
    io.bTag2 = IL_STER | IL_TYPS;

    // Allocate strbuf
    char buf[16] = {0};
    strbuf.pStr = buf;
    strbuf.nAllocatedLength = sizeof(buf);
    strbuf.nUsedLength = 0;

    // Call function
    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    // The stereo type should be "s1" (plain tag + abs)
    EXPECT_EQ(std::string(strbuf.pStr), "/s1");
    EXPECT_EQ(ret, 0);
}

TEST(test_ichiprt1, OutputINCHI_StereoLayer_s2)
{
    // Prepare minimal input structures
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};

    // Set up io to trigger the /s (stereo type) segment
    io.sDifSegs[0][DIFS_s_STYPE] = DIFV_OUTPUT_FILL_T; // nonzero triggers INChI_SegmentAction


    io.nCurINChISegment = 0;
    io.iCurTautMode = 0;
    io.bPlainTextTags = 1;
    io.bRelativeStereo[0] = 1;
    io.bRacemicStereo[0] = 0;
    io.bAlways = 0;
    io.nTag = 2; // plain text
    io.bTag1 = IL_STER;
    io.bTag2 = IL_STER | IL_TYPS;

    // Allocate strbuf
    char buf[16] = {0};
    strbuf.pStr = buf;
    strbuf.nAllocatedLength = sizeof(buf);
    strbuf.nUsedLength = 0;

    // Call function
    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    // The stereo type should be "s1" (plain tag + abs)
    EXPECT_EQ(std::string(strbuf.pStr), "/s2");
    EXPECT_EQ(ret, 0);
}

TEST(test_ichiprt1, OutputINCHI_StereoLayer_s3)
{
    // Prepare minimal input structures
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};

    // Set up io to trigger the /s (stereo type) segment
    io.sDifSegs[0][DIFS_s_STYPE] = DIFV_OUTPUT_FILL_T; // nonzero triggers INChI_SegmentAction


    io.nCurINChISegment = 0;
    io.iCurTautMode = 0;
    io.bPlainTextTags = 1;
    io.bRelativeStereo[0] = 0;
    io.bRacemicStereo[0] = 1;
    io.bAlways = 0;
    io.nTag = 2; // plain text
    io.bTag1 = IL_STER;
    io.bTag2 = IL_STER | IL_TYPS;

    // Allocate strbuf
    char buf[16] = {0};
    strbuf.pStr = buf;
    strbuf.nAllocatedLength = sizeof(buf);
    strbuf.nUsedLength = 0;

    // Call function
    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    // The stereo type should be "s1" (plain tag + abs)
    EXPECT_EQ(std::string(strbuf.pStr), "/s3");
    EXPECT_EQ(ret, 0);
}

TEST(test_ichiprt1, test_set_line_separators)
{

    // void set_line_separators( int bINChIOutputOptions, char **pLF, char **pTAB )

    char *lf = nullptr;
    char *tab = nullptr;

    // Plain text comments option
    set_line_separators(INCHI_OUT_PLAIN_TEXT_COMMENTS, &lf, &tab);
    EXPECT_STREQ(lf, "\n");
    EXPECT_STREQ(tab, "\n");

    // Tabbed output option
    set_line_separators(INCHI_OUT_PLAIN_TEXT | INCHI_OUT_TABBED_OUTPUT, &lf, &tab);
    EXPECT_STREQ(lf, "\0");
    EXPECT_STREQ(tab, "\t");

    // Plain text only
    set_line_separators(INCHI_OUT_PLAIN_TEXT, &lf, &tab);
    EXPECT_STREQ(lf, "\0");
    EXPECT_STREQ(tab, "\n");

    // No options
    set_line_separators(0, &lf, &tab);
    EXPECT_STREQ(lf, "\0");
    EXPECT_STREQ(tab, "\n");


}
