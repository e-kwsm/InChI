#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichiprt3.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/strutil.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichimake.h"
}

TEST(test_ichiprt3, test_str_Sp2_outputs_expected_sp2_string_1)
{
    int num_at = 2;
    int num_bonds = 1;
    int bond_atom1[1] = {4};
    int bond_atom2[1] = {3};
    S_CHAR b_parity[1] = {1}; // 1 = -, 2 = +

    INChI_Stereo* stereo = Alloc_INChI_Stereo(num_at, num_bonds);
    stereo->nNumberOfStereoBonds = num_bonds;
    for (int i = 0; i < num_bonds; i++) {
        stereo->nBondAtom1[i] = bond_atom1[i];
        stereo->nBondAtom2[i] = bond_atom2[i];
        stereo->b_parity[i] = b_parity[i];
    }

    INChI inchi = {0};
    inchi.nNumberOfAtoms = num_at;
    inchi.Stereo = stereo;

    INCHI_SORT inchi_sort = {0};
    inchi_sort.pINChI[0] = &inchi;

    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    int bOverflow = 0;
    int bOutputType = OUT_N1; // OUT_TN
    int taut_mode = 0; // CT_MODE_ABC_NUMBERS
    int num_components = 1;

    int bSecondNonTautPass = 0;
    int bOmitRepetitions = 0;
    int bUseMulipliers = 1;

    int ret = str_Sp2(
        &inchi_sort,
        NULL,
        &strbuf,
        &bOverflow,
        bOutputType,
        taut_mode,
        num_components,
        bSecondNonTautPass,
        bOmitRepetitions,
        bUseMulipliers
    );

    EXPECT_EQ(strbuf.nUsedLength, strlen(strbuf.pStr));
    EXPECT_EQ(std::string(strbuf.pStr), "4-3-");
    EXPECT_EQ(strbuf.pStr[0], '4');
    EXPECT_EQ(bOverflow, 0);

    // The return value should be the length of the output string
    EXPECT_EQ(ret, 4);

    inchi_strbuf_close(&strbuf);
    Free_INChI_Stereo(stereo);
    inchi_free(stereo);
}

TEST(test_ichiprt3, test_str_Sp2_outputs_expected_sp2_string_2)
{
    int num_at = 4;
    int num_bonds = 2;
    int bond_atom1[2] = {1, 3};
    int bond_atom2[2] = {2, 4};
    S_CHAR b_parity[2] = {1, 2}; // 1 = -, 2 = +

    INChI_Stereo* stereo = Alloc_INChI_Stereo(num_at, num_bonds);
    stereo->nNumberOfStereoBonds = num_bonds;
    for (int i = 0; i < num_bonds; i++) {
        stereo->nBondAtom1[i] = bond_atom1[i];
        stereo->nBondAtom2[i] = bond_atom2[i];
        stereo->b_parity[i] = b_parity[i];
    }

    INChI inchi = {0};
    inchi.nNumberOfAtoms = num_at;
    inchi.Stereo = stereo;

    INCHI_SORT inchi_sort = {0};
    inchi_sort.pINChI[0] = &inchi;

    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    int bOverflow = 0;
    int bOutputType = OUT_N1; // OUT_TN
    int taut_mode = 0; // CT_MODE_ABC_NUMBERS
    int num_components = 1;

    int bSecondNonTautPass = 0;
    int bOmitRepetitions = 0;
    int bUseMulipliers = 1;

    int ret = str_Sp2(
        &inchi_sort,
        NULL,
        &strbuf,
        &bOverflow,
        bOutputType,
        taut_mode,
        num_components,
        bSecondNonTautPass,
        bOmitRepetitions,
        bUseMulipliers
    );

    EXPECT_EQ(strbuf.nUsedLength, strlen(strbuf.pStr));
    EXPECT_EQ(std::string(strbuf.pStr), "1-2-,3-4+");
    EXPECT_EQ(strbuf.pStr[0], '1');
    EXPECT_EQ(bOverflow, 0);

    // The return value should be the length of the output string
    EXPECT_EQ(ret, 9);

    inchi_strbuf_close(&strbuf);
    Free_INChI_Stereo(stereo);
    inchi_free(stereo);
}

TEST(test_ichiprt3, test_str_Sp3_outputs_expected_sp3_string)
{
    int numbers[8] = {3,4,5,6,7,8,9,10};
    S_CHAR parities[8] = {1,1,2,2,1,2,2,1}; // 1 = -, 2 = +
    int num_at = 8;
    static INChI_Stereo *stereo = Alloc_INChI_Stereo( num_at, 0 );
    stereo->nNumberOfStereoCenters = num_at;

    for (int i = 0; i < num_at; i++) {
        stereo->nNumber[i] = numbers[i];
        stereo->t_parity[i] = parities[i];
    }

    INChI inchi = {0};
    inchi.nNumberOfAtoms = 10;
    inchi.Stereo = stereo;

    INCHI_SORT inchi_sort = {0};
    inchi_sort.pINChI[0] = &inchi;

    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);


    int bOverflow = 0;
    int num_components = 1;

    int bIsotopicRelativeStereo = 0; // INCHI_FLAG_REL_STEREO
    int bIsotopicRacemicStereo = 0; // INCHI_FLAG_RAC_STEREO

    int bRelRac = bIsotopicRelativeStereo || bIsotopicRacemicStereo;

    int ret = str_Sp3(&inchi_sort, NULL, &strbuf, &bOverflow, 0, 0, num_components, bRelRac, 0, 0, 0);

    EXPECT_EQ(strbuf.nUsedLength, strlen(strbuf.pStr));
    EXPECT_EQ(std::string(strbuf.pStr), "3-,4-,5+,6+,7-,8+,9+,10-");
    EXPECT_EQ(strbuf.pStr[0], '3');
    EXPECT_EQ(bOverflow, 0);

    EXPECT_EQ(ret, 24);

    inchi_strbuf_close(&strbuf);

    Free_INChI_Stereo(stereo);
}

TEST(test_ichiprt3, test_str_StereoAbsInv_1)
{

    int num_at = 2;
    int num_bonds = 1;
    int found_num_bonds = 0;
    int found_num_isotopic = 0;
    inp_ATOM *at = CreateInpAtom(num_at);
    INChI *inchi = Alloc_INChI(at, num_at, &found_num_bonds, &found_num_isotopic, 0);
    inchi->Stereo->nCompInv2Abs = -1;
    inchi->nNumberOfAtoms = num_at;

    INCHI_SORT *inchi_sort = (INCHI_SORT*)calloc(1, sizeof(INCHI_SORT));
    inchi_sort->pINChI[TAUT_YES] = inchi;

    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    int bOverflow = 0;
    int bOutType = OUT_TN;
    int num_components = 1;

    // int test_ret0 = HAS_T(inchi_sort);
    // int test_ret1 = GET_II( bOutType, inchi_sort);

    int ret = str_StereoAbsInv(inchi_sort, &strbuf, &bOverflow, bOutType, num_components);

    EXPECT_EQ(ret, 1);
    EXPECT_EQ(std::string(strbuf.pStr), "1");
    EXPECT_EQ(bOverflow, 0);

    inchi_strbuf_close(&strbuf);

    Free_INChI(&inchi);

    FreeInpAtom(&at);

    free(inchi_sort);
}

TEST(test_ichiprt3, test_str_StereoAbsInv_2)
{

    int num_at = 2;
    int num_bonds = 1;
    int found_num_bonds = 0;
    int found_num_isotopic = 0;
    inp_ATOM *at = CreateInpAtom(num_at);
    static INChI *inchi = Alloc_INChI(at, num_at, &found_num_bonds, &found_num_isotopic, 0);

    inchi->Stereo->nCompInv2Abs = 1;

    inchi->nNumberOfAtoms = num_at;

    INCHI_SORT *inchi_sort = (INCHI_SORT*)calloc(1, sizeof(INCHI_SORT));
    inchi_sort->pINChI[TAUT_YES] = inchi;

    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    int bOverflow = 0;
    int bOutType = OUT_TN;
    int num_components = 1;

    // int test_ret0 = HAS_T(inchi_sort);
    // int test_ret1 = GET_II( bOutType, inchi_sort);

    int ret = str_StereoAbsInv(inchi_sort, &strbuf, &bOverflow, bOutType, num_components);

    EXPECT_EQ(ret, 1);
    EXPECT_EQ(std::string(strbuf.pStr), "0");
    EXPECT_EQ(bOverflow, 0);

    inchi_strbuf_close(&strbuf);

    Free_INChI(&inchi);

    FreeInpAtom(&at);

    free(inchi_sort);
}
