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
#include "../../../INCHI-1-SRC/INCHI_BASE/src/strutil.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichimake.h"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichicano.h"
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
    inchi_ios_init(&out_file, INCHI_IOS_TYPE_STRING, nullptr);

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

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_s1)
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

    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);
    inchi_ios_init(&out_file, INCHI_IOS_TYPE_STRING, nullptr);

    // Call function
    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    // The stereo type should be "s1" (plain tag + abs)
    EXPECT_EQ(std::string(strbuf.pStr), "/s1");
    EXPECT_EQ(ret, 0);

    inchi_strbuf_close(&strbuf);
    inchi_ios_close(&out_file);
}

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_s2)
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

    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);
    inchi_ios_init(&out_file, INCHI_IOS_TYPE_STRING, nullptr);

    // Call function
    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    // The stereo type should be "s1" (plain tag + abs)
    EXPECT_EQ(std::string(strbuf.pStr), "/s2");
    EXPECT_EQ(ret, 0);

    inchi_strbuf_close(&strbuf);
    inchi_ios_close(&out_file);
}

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_s3)
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

    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);
    inchi_ios_init(&out_file, INCHI_IOS_TYPE_STRING, nullptr);

    // Call function
    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    // The stereo type should be "s1" (plain tag + abs)
    EXPECT_EQ(std::string(strbuf.pStr), "/s3");
    EXPECT_EQ(ret, 0);

    inchi_strbuf_close(&strbuf);
    inchi_ios_close(&out_file);
}

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_enh_stereo_1)
{
    // --- Setup CANON_GLOBALS and INChI/INChI_Stereo for enhanced stereo ---
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};

    int num_at = 8;
    int num_bonds = 0;
    static AT_NUMB numbers[8] = {3,4,5,6,7,8,9,10};
    static S_CHAR parities[8] = {1,1,2,2,1,2,2,1};// -,-,+,+,-,+,+,-

    static S_CHAR m_values[1] = {0}; // /m0
    static S_CHAR s_values[1] = {1}; // /s1

    // static INChI_Stereo stereo = {0};

    static INChI_Stereo *stereo = Alloc_INChI_Stereo( num_at, num_bonds );

    stereo->nNumberOfStereoCenters = 8;

    for (int i = 0; i < num_at; i++) {
        stereo->nNumber[i] = numbers[i];
        stereo->t_parity[i] = parities[i];
    }

    stereo->nCompInv2Abs = 1;
    stereo->nNumberOfStereoBonds = 0;
    stereo->b_parity = NULL;

    // INChI *inchi = new INChI;
    // inchi->nNumberOfAtoms = num_at;
    // inchi->Stereo = stereo;

    int found_num_bonds = 0;
    int found_num_isotopic = 0;
    inp_ATOM *at = CreateInpAtom(num_at);
    static INChI *inchi = Alloc_INChI(at, num_at, &found_num_bonds, &found_num_isotopic, 0);

    inchi->nNumberOfAtoms = num_at;
    inchi->Stereo = stereo;

    static INCHI_SORT sort = {0};
    sort.pINChI[0] = inchi;

    io.pINChISort = &sort;

    // --- Setup io to trigger stereo output ---
    io.num_components = 1;
    io.bRelativeStereo[0] = 0;
    io.bRacemicStereo[0] = 1;

    io.sDifSegs[0][DIFS_t_SATOMS] = DIFV_OUTPUT_FILL_T;
    io.sDifSegs[0][DIFS_m_SP3INV] = DIFV_OUTPUT_FILL_T;
    io.sDifSegs[0][DIFS_s_STYPE] = DIFV_OUTPUT_FILL_T;
    io.nCurINChISegment = 0;
    io.iCurTautMode = 0;
    io.bPlainTextTags = 1;
    io.nTag = 2;
    io.bTag1 = IL_STER;
    io.bTag2 = IL_STER | IL_TYPS;
    io.bOutType = OUT_TN;

    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);
    inchi_ios_init(&out_file, INCHI_IOS_TYPE_STRING, nullptr);

    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    EXPECT_EQ(std::string(out_file.s.pStr), "//t3-,4-,5+,6+,7-,8+,9+,10-/m0/s3/");
    EXPECT_EQ(ret, 0);

    inchi_strbuf_close(&strbuf);
    inchi_ios_close(&out_file);

    FreeInpAtom(&at);
    // Free_INChI(&inchi);
    Free_INChI_Stereo(stereo);
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
