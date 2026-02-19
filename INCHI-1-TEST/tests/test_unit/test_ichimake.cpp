#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>
#include <vector>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichimake.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
}

TEST(test_ichimake, test_GetSp3RelRacAbs_none)
{

    INChI inchi = {0};
    INChI_Stereo stereo = {0};

    stereo.nNumberOfStereoCenters = 0;

    // pINChI->bDeleted
    // Stereo->nCompInv2Abs
    // 0: No inversion (structure unchanged by inversion)
    // Positive integer (>0): Indicates inversion changes the structure (normal/absolute stereo)
    // Negative integer (<0): Indicates inversion changes the structure (inverted/absolute stereo)

    //int GetSp3RelRacAbs(const INChI* pINChI, INChI_Stereo* Stereo);

    int result = GetSp3RelRacAbs(&inchi, &stereo);

    EXPECT_EQ(result, SP3_NONE);

}

TEST(test_ichimake, test_GetSp3RelRacAbs_sp3)
{
    INChI inchi = {0};
    INChI_Stereo stereo = {0};

    stereo.nNumberOfStereoCenters = 1;
    stereo.nCompInv2Abs = 0;

    int result = GetSp3RelRacAbs(&inchi, &stereo);

    EXPECT_EQ(result, SP3_ONLY);
}

TEST(test_ichimake, test_GetSp3RelRacAbs_rel)
{
    INChI inchi = {0};
    INChI_Stereo stereo = {0};

    inchi.nFlags = INCHI_FLAG_REL_STEREO;
    stereo.nNumberOfStereoCenters = 1;
    stereo.nCompInv2Abs = 1;

    int result = GetSp3RelRacAbs(&inchi, &stereo);

    EXPECT_EQ(result, SP3_REL);
}

TEST(test_ichimake, test_GetSp3RelRacAbs_rac)
{
    INChI inchi = {0};
    INChI_Stereo stereo = {0};

    inchi.nFlags = INCHI_FLAG_RAC_STEREO;
    stereo.nNumberOfStereoCenters = 1;
    stereo.nCompInv2Abs = 1;

    int result = GetSp3RelRacAbs(&inchi, &stereo);

    EXPECT_EQ(result, SP3_RAC);
}

TEST(test_ichimake, test_GetSp3RelRacAbs_abs)
{
    INChI inchi = {0};
    INChI_Stereo stereo = {0};

    inchi.nFlags = 0x0111;
    stereo.nNumberOfStereoCenters = 1;
    stereo.nCompInv2Abs = 1;

    int result = GetSp3RelRacAbs(&inchi, &stereo);

    EXPECT_EQ(result, SP3_ABS);
}
