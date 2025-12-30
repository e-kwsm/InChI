#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichiprt3.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/strutil.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
}

TEST(test_ichiprt3, test_str_Sp3_outputs_expected_sp3_string)
{
    int numbers[8] = {3,4,5,6,7,8,9,10};
    S_CHAR parities[8] = {1,1,2,2,1,2,2,1};
    int num_at = 8;
    static INChI_Stereo *stereo = Alloc_INChI_Stereo( num_at, 0 );
    stereo->nNumberOfStereoCenters = num_at;

    // INChI_Stereo stereo = {0};
    // stereo.nNumberOfStereoCenters = 8;
    // stereo.t_parity = (S_CHAR*)inchi_calloc((long long)stereo.nNumberOfStereoCenters, sizeof(S_CHAR));
    // stereo.nNumber = (AT_NUMB*)inchi_calloc((long long)stereo.nNumberOfStereoCenters, sizeof(AT_NUMB));

    for (int i = 0; i < num_at; i++) {
        stereo->nNumber[i] = numbers[i];
        stereo->t_parity[i] = parities[i];
    }

    INChI inchi = {0};
    inchi.nNumberOfAtoms = 10;
    inchi.Stereo = stereo;

    INCHI_SORT sort = {0};
    sort.pINChI[0] = &inchi;

    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);


    int bOverflow = 0;
    int ret = str_Sp3(&sort, NULL, &strbuf, &bOverflow, 0, 0, 1, 0, 0, 0, 0);

    // Check that strbuf contains the expected substring
    EXPECT_EQ(strbuf.nUsedLength, strlen(strbuf.pStr));
    // EXPECT_NE(std::string(strbuf.pStr).find("3-,4-,5+,6+,7-,8+,9+,10-"), std::string::npos);
    EXPECT_EQ(std::string(strbuf.pStr), "3-,4-,5+,6+,7-,8+,9+,10-");
    EXPECT_EQ(strbuf.pStr[0], '3'); // Should start with 3-
    EXPECT_EQ(bOverflow, 0);

    EXPECT_EQ(ret, 24);

    inchi_strbuf_close(&strbuf);

    Free_INChI_Stereo(stereo);
}
