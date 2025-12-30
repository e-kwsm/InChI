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

    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};
    char lf[] = "\n";
    char tab[] = "\t";

    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);
    inchi_ios_init(&out_file, INCHI_IOS_TYPE_STRING, nullptr);

    // int OutputINCHI_StereoLayer( CANON_GLOBALS    *pCG,
    //                             INCHI_IOSTREAM   *out_file,
    //                             INCHI_IOS_STRING *strbuf,
    //                             INCHI_OUT_CTL    *io,
    //                             char             *pLF,
    //                             char             *pTAB )

    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, lf, tab);

    EXPECT_EQ(ret, 0);

    // Clean up
    inchi_strbuf_close(&strbuf);

}

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_s1)
{
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};

    io.sDifSegs[0][DIFS_s_STYPE] = DIFV_OUTPUT_FILL_T;

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

    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    EXPECT_EQ(std::string(strbuf.pStr), "/s1");
    EXPECT_EQ(ret, 0);

    inchi_strbuf_close(&strbuf);
    inchi_ios_close(&out_file);
}

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_s2)
{
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};

    io.sDifSegs[0][DIFS_s_STYPE] = DIFV_OUTPUT_FILL_T;

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

    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    EXPECT_EQ(std::string(strbuf.pStr), "/s2");
    EXPECT_EQ(ret, 0);

    inchi_strbuf_close(&strbuf);
    inchi_ios_close(&out_file);
}

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_s3)
{
    CANON_GLOBALS cg = {0};
    INCHI_IOSTREAM out_file = {0};
    INCHI_IOS_STRING strbuf = {0};
    INCHI_OUT_CTL io = {0};


    io.sDifSegs[0][DIFS_s_STYPE] = DIFV_OUTPUT_FILL_T;

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

    int ret = OutputINCHI_StereoLayer(&cg, &out_file, &strbuf, &io, (char*)"", (char*)"");

    EXPECT_EQ(std::string(strbuf.pStr), "/s3");
    EXPECT_EQ(ret, 0);

    inchi_strbuf_close(&strbuf);
    inchi_ios_close(&out_file);
}

TEST(test_ichiprt1, test_OutputINCHI_StereoLayer_enh_stereo_1)
{
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

    io.num_components = 1;
    io.bRelativeStereo[0] = 0;
    io.bRacemicStereo[0] = 1;

    io.sDifSegs[0][DIFS_b_SBONDS] = DIFV_OUTPUT_FILL_T;
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

    EXPECT_EQ(std::string(out_file.s.pStr), "/t3-,4-,5+,6+,7-,8+,9+,10-/m0/s3/");
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

TEST(test_ichiprt1, test_szGetTag_basic)
{

    // nTag = 1: XML label (szXmlLabel)
    // nTag = 2: Plain text label (szPlainLabel)
    // nTag = 3: Plain label with comments (sometimes)

    // bTag: A bitmask indicating which tag (or tags) to look up in the INCHI_TAG array.

    char szTag[64] = {0};
    int bAlways = -1;

    EXPECT_STREQ(szGetTag(IdentLbl, 0, 0, szTag, &bAlways, 0), "???"); //fixed-H
    EXPECT_STREQ(szTag, "???");

}

TEST(test_ichiprt1, test_szGetTag_returns_unknown_for_invalid_index)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 0, bTag = 0, should return "???"
    EXPECT_STREQ(szGetTag(IdentLbl, 0, 0, szTag, &bAlways, 0), "???");
    EXPECT_STREQ(szTag, "???");
}

TEST(test_ichiprt1, test_szGetTag_stereo_1)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_STER (stereo)
    EXPECT_STREQ(szGetTag(IdentLbl, 2, IL_STER, szTag, &bAlways, 0), "/");
    EXPECT_STREQ(szTag, "/");
}

TEST(test_ichiprt1, test_szGetTag_stereo_2)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_STER (stereo)
    EXPECT_STREQ(szGetTag(IdentLbl, 1, IL_STER, szTag, &bAlways, 0), "stereo");
    EXPECT_STREQ(szTag, "stereo");
}

TEST(test_ichiprt1, test_szGetTag_stereo_3)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_STER (stereo)
    EXPECT_STREQ(szGetTag(IdentLbl, 2, IL_SP3S, szTag, &bAlways, 0), "/t");
    EXPECT_STREQ(szTag, "/t");
}

TEST(test_ichiprt1, test_szGetTag_stereo_4)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_STER (stereo)
    EXPECT_STREQ(szGetTag(IdentLbl, 2, IL_INVS, szTag, &bAlways, 0), "/m");
    EXPECT_STREQ(szTag, "/m");
}

TEST(test_ichiprt1, test_szGetTag_stereo_5)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_STER (stereo)
    EXPECT_STREQ(szGetTag(IdentLbl, 2, IL_TYPS, szTag, &bAlways, 0), "/s");
    EXPECT_STREQ(szTag, "/s");
}

TEST(test_ichiprt1, test_szGetTag_stereo_6)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_STER (stereo)
    EXPECT_STREQ(szGetTag(IdentLbl, 1, IL_TYPS, szTag, &bAlways, 0), "type");
    EXPECT_STREQ(szTag, "type");
}

TEST(test_ichiprt1, test_szGetTag_hfixed)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_STER (stereo)
    EXPECT_STREQ(szGetTag(IdentLbl, 1, IL_FIXH, szTag, &bAlways, 0), "fixed-H");
    EXPECT_STREQ(szTag, "fixed-H");
}

TEST(test_ichiprt1, test_szGetTag_returns_xml_label)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 1 (XML), bTag = IL_CONN (connections)
    EXPECT_STREQ(szGetTag(IdentLbl, 1, IL_CONN, szTag, &bAlways, 0), "connections");
    EXPECT_STREQ(szTag, "connections");
}

TEST(test_ichiprt1, test_szGetTag_sets_bAlways)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_FML_ (formula), which has bAlwaysOutput = 1
    szGetTag(IdentLbl, 2, IL_FML_, szTag, &bAlways, 0);
    EXPECT_EQ(bAlways, -1);
    EXPECT_STREQ(szTag, "/");
}

TEST(test_ichiprt1, test_szGetTag_charge)
{
    char szTag[64] = {0};
    int bAlways = -1;
    // nTag = 2 (plain text), bTag = IL_CHRG (charge)
    EXPECT_STREQ(szGetTag(IdentLbl, 2, IL_CHRG, szTag, &bAlways, 0), "/q");
    EXPECT_STREQ(szTag, "/q");
}
