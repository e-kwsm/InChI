#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>
#include <vector>

extern "C"
{
// #include "../../../INCHI-1-SRC/INCHI_BASE/src/ichitime.h"
// #include "../../../INCHI-1-SRC/INCHI_BASE/src/ichicant.h"
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
