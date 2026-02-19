#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/inpdef.h"
}

TEST(test_inpdef, test_CreateOrigInpDataFromMolfile_v3000_sgroup)
{

    INCHI_IOSTREAM input_stream;

    const char *molblock =
        "enhanc_stereo1									  \n"
        "  ACD/LABS08242216132D                            \n"
        "												  \n"
        "  0  0  0  0  0  0  0  0  0  0999 V3000           \n"
        "M  V30 BEGIN CTAB                                 \n"
        "M  V30 COUNTS 18 17 0 0 1                         \n"
        "M  V30 BEGIN ATOM                                 \n"
        "M  V30 1 C 3424.1946 -1936.7935 0 0               \n"
        "M  V30 2 C 3352.3145 -1895.2935 0 0               \n"
        "M  V30 3 C 3280.4346 -1936.7935 0 0               \n"
        "M  V30 4 C 3208.5542 -1895.2935 0 0               \n"
        "M  V30 5 C 3136.6743 -1936.7935 0 0               \n"
        "M  V30 6 C 3064.7944 -1895.2935 0 0               \n"
        "M  V30 7 Br 3136.6743 -2019.7935 0 0              \n"
        "M  V30 8 Cl 3208.5542 -1812.2935 0 0              \n"
        "M  V30 9 Cl 3280.4346 -2019.7935 0 0              \n"
        "M  V30 10 Cl 3352.3145 -1812.2935 0 0             \n"
        "M  V30 11 Cl 3424.1946 -2019.7935 0 0             \n"
        "M  V30 12 C 3496.075 -1895.2935 0 0               \n"
        "M  V30 13 C 3567.9548 -1936.7942 0 0              \n"
        "M  V30 14 C 3639.835 -1895.2944 0 0               \n"
        "M  V30 15 C 3711.7148 -1936.7942 0 0              \n"
        "M  V30 16 Cl 3639.835 -1812.2944 0 0              \n"
        "M  V30 17 Cl 3567.9548 -2019.7942 0 0             \n"
        "M  V30 18 Cl 3496.075 -1812.2937 0 0              \n"
        "M  V30 END ATOM                                   \n"
        "M  V30 BEGIN BOND                                 \n"
        "M  V30 1 1 1 2                                    \n"
        "M  V30 2 1 1 11 CFG=3                             \n"
        "M  V30 3 1 1 12                                   \n"
        "M  V30 4 1 2 3                                    \n"
        "M  V30 5 1 2 10 CFG=1                             \n"
        "M  V30 6 1 3 4                                    \n"
        "M  V30 7 1 3 9 CFG=1                              \n"
        "M  V30 8 1 4 5                                    \n"
        "M  V30 9 1 4 8 CFG=1                              \n"
        "M  V30 10 1 5 6                                   \n"
        "M  V30 11 1 5 7 CFG=1                             \n"
        "M  V30 12 1 12 13                                 \n"
        "M  V30 13 1 12 18 CFG=3                           \n"
        "M  V30 14 1 13 14                                 \n"
        "M  V30 15 1 13 17 CFG=1                           \n"
        "M  V30 16 1 14 15                                 \n"
        "M  V30 17 1 14 16 CFG=1                           \n"
        "M  V30 END BOND                                   \n"
        "M  V30 BEGIN COLLECTION                           \n"
        "M  V30 MDLV30/STERAC2 ATOMS=(1 1)                 \n"
        "M  V30 MDLV30/STERAC1 ATOMS=(2 2 3)               \n"
        "M  V30 MDLV30/STEABS ATOMS=(2 4 5)                \n"
        "M  V30 MDLV30/STEREL1 ATOMS=(2 12 13)             \n"
        "M  V30 MDLV30/STEREL2 ATOMS=(1 14)                \n"
        "M  V30 END COLLECTION                             \n"
        "M  V30 END CTAB                                   \n"
        "M  END                                            \n";

    inchi_ios_init(&input_stream, INCHI_IOS_TYPE_STRING, nullptr);
    inchi_ios_print_nodisplay(&input_stream, molblock);

    // int ret = CreateOrigInpDataFromMolfile(
    //     INCHI_IOSTREAM *inp_file,
    //     ORIG_ATOM_DATA *orig_at_data,
    //     int bMergeAllInputStructures,
    //     int bGetOrigCoord,
    //     int bDoNotAddH,
    //     int treat_polymers,
    //     int treat_NPZz,
    //     const char *pSdfLabel,
    //     char *pSdfValue,
    //     unsigned long *lSdfId,
    //     long *lMolfileNumber,
    //     INCHI_MODE *pInpAtomFlags,
    //     int *err,
    //     char *pStrErr,
    //     int bNoWarnings);

    ORIG_ATOM_DATA orig_at_data = {};
    int bMergeAllInputStructures = 0;
    int bGetOrigCoord = 0;
    int bDoNotAddH = 0;
    int treat_polymers = 0;
    int treat_NPZz = 0;
    const char *pSdfLabel = nullptr;
    char *pSdfValue = nullptr;
    unsigned long *lSdfId = nullptr;
    long *lMolfileNumber = nullptr;
    INCHI_MODE pInpAtomFlags = 0;
    int err = 0;
    char *pStrErr = nullptr;
    int bNoWarnings = 0;

    int ret = CreateOrigInpDataFromMolfile(
        &input_stream,
        &orig_at_data,
        bMergeAllInputStructures,
        bGetOrigCoord,
        bDoNotAddH,
        treat_polymers,
        treat_NPZz,
        pSdfLabel,
        pSdfValue,
        lSdfId,
        lMolfileNumber,
        &pInpAtomFlags,
        &err,
        pStrErr,
        bNoWarnings);

    EXPECT_EQ(ret, 18);
    EXPECT_EQ(orig_at_data.num_inp_atoms, 18);
    EXPECT_EQ(orig_at_data.num_inp_bonds, 17);

    EXPECT_EQ(orig_at_data.v3000->n_steabs, 1);

    // STEABS ATOMS=(2 4 5)
    EXPECT_EQ(orig_at_data.v3000->lists_steabs[0][0], 1); // - not used
    EXPECT_EQ(orig_at_data.v3000->lists_steabs[0][1], 2); // number of members in collection
    EXPECT_EQ(orig_at_data.v3000->lists_steabs[0][2], 4); //  member atom numbers
    EXPECT_EQ(orig_at_data.v3000->lists_steabs[0][3], 5); //  member atom numbers

    // STERAC2 ATOMS=(1 1)
    EXPECT_EQ(orig_at_data.v3000->n_sterac, 2);

    EXPECT_EQ(orig_at_data.v3000->lists_sterac[0][0], 2); // n from "STERACn" tag
    EXPECT_EQ(orig_at_data.v3000->lists_sterac[0][1], 1); // number of members in collection
    EXPECT_EQ(orig_at_data.v3000->lists_sterac[0][2], 1); // member atom numbers

    // STERAC1 ATOMS=(2 2 3)
    EXPECT_EQ(orig_at_data.v3000->lists_sterac[1][0], 1); // STERAC1 ATOMS=(2 2 3)
    EXPECT_EQ(orig_at_data.v3000->lists_sterac[1][1], 2); // number of members in collection
    EXPECT_EQ(orig_at_data.v3000->lists_sterac[1][2], 2); // member atom numbers
    EXPECT_EQ(orig_at_data.v3000->lists_sterac[1][3], 3); // member atom numbers

    EXPECT_EQ(orig_at_data.v3000->n_sterel, 2);

    // STEREL1 ATOMS=(2 12 13) or1
    EXPECT_EQ(orig_at_data.v3000->lists_sterel[0][0], 1);  // n from "STERELn" tag
    EXPECT_EQ(orig_at_data.v3000->lists_sterel[0][1], 2);  // number of members in collection
    EXPECT_EQ(orig_at_data.v3000->lists_sterel[0][2], 12); // member atom numbers
    EXPECT_EQ(orig_at_data.v3000->lists_sterel[0][3], 13); // member atom numbers

    // STEREL2 ATOMS=(1 14) or2
    EXPECT_EQ(orig_at_data.v3000->lists_sterel[1][0], 2);  // n from "STERELn" tag
    EXPECT_EQ(orig_at_data.v3000->lists_sterel[1][1], 1);  // number of members in collection
    EXPECT_EQ(orig_at_data.v3000->lists_sterel[1][2], 14); // member atom numbers

    inchi_ios_free_str(&input_stream);
    FreeOrigAtData(&orig_at_data);
}
