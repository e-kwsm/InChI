#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichiprt2.c"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
}

TEST(test_ichiprt2, MakeStereoString_outputs_expected_sp3_string)
{
    AT_NUMB at1[8] = {3,4,5,6,7,8,9,10};
    S_CHAR parity[8] = {1,1,2,2,1,2,2,1};

    INCHI_IOS_STRING strbuf = {0};

    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    int bOverflow = 0;
    int ret = MakeStereoString(at1, nullptr, parity, 0, 8, &strbuf, 0, &bOverflow);

    EXPECT_EQ(strbuf.nUsedLength, strlen(strbuf.pStr));
    EXPECT_NE(std::string(strbuf.pStr).find("3-,4-,5+,6+,7-,8+,9+,10-"), std::string::npos);
    EXPECT_EQ(std::string(strbuf.pStr), "3-,4-,5+,6+,7-,8+,9+,10-");
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

TEST(test_ichiprt2, MakeMult_mult_2)
{
    INCHI_IOS_STRING strbuf = {0};
    inchi_strbuf_init(&strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT);

    int bOverflow = 0;
    int ret = MakeMult(10, "+", &strbuf, 0, &bOverflow);

    EXPECT_EQ(std::string(strbuf.pStr), "10+");
    EXPECT_EQ(ret, 3); // "3-".length() == 2, but MakeMult returns n (number of chars written)
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

TEST(test_ichiprt2, Eql_INChI_Stereo_sp2_equal)
{
    // Setup two identical SP2 stereo objects
    INChI_Stereo s1 = {0}, s2 = {0};
    int num_bonds = 2;
    AT_NUMB bond_atom1[2] = {1, 3};
    AT_NUMB bond_atom2[2] = {2, 4};
    S_CHAR b_parity[2] = {1, 2};

    s1.nNumberOfStereoBonds = num_bonds;
    s1.nBondAtom1 = bond_atom1;
    s1.nBondAtom2 = bond_atom2;
    s1.b_parity = b_parity;

    s2.nNumberOfStereoBonds = num_bonds;
    s2.nBondAtom1 = bond_atom1;
    s2.nBondAtom2 = bond_atom2;
    s2.b_parity = b_parity;

    // Should be equal
    EXPECT_EQ(Eql_INChI_Stereo(&s1, EQL_SP2, &s2, EQL_SP2, 0), 1);
}

TEST(test_ichiprt2, Eql_INChI_Stereo_sp2_not_equal)
{
    // Setup two different SP2 stereo objects
    INChI_Stereo s1 = {0}, s2 = {0};
    AT_NUMB bond_atom1_1[2] = {1, 3};
    AT_NUMB bond_atom2_1[2] = {2, 4};
    S_CHAR b_parity_1[2] = {1, 2};

    AT_NUMB bond_atom1_2[2] = {1, 5};
    AT_NUMB bond_atom2_2[2] = {2, 6};
    S_CHAR b_parity_2[2] = {1, 1};

    s1.nNumberOfStereoBonds = 2;
    s1.nBondAtom1 = bond_atom1_1;
    s1.nBondAtom2 = bond_atom2_1;
    s1.b_parity = b_parity_1;

    s2.nNumberOfStereoBonds = 2;
    s2.nBondAtom1 = bond_atom1_2;
    s2.nBondAtom2 = bond_atom2_2;
    s2.b_parity = b_parity_2;

    // Should not be equal
    EXPECT_EQ(Eql_INChI_Stereo(&s1, EQL_SP2, &s2, EQL_SP2, 0), 0);
}

TEST(test_ichiprt2, Eql_INChI_Stereo_sp2_exists)
{
    // s1 has stereo, s2 is nullptr, eql2 is EQL_EXISTS
    INChI_Stereo s1 = {0};
    AT_NUMB bond_atom1[1] = {1};
    AT_NUMB bond_atom2[1] = {2};
    S_CHAR b_parity[1] = {1};

    s1.nNumberOfStereoBonds = 1;
    s1.nBondAtom1 = bond_atom1;
    s1.nBondAtom2 = bond_atom2;
    s1.b_parity = b_parity;

    EXPECT_EQ(Eql_INChI_Stereo(&s1, EQL_SP2, nullptr, EQL_EXISTS, 0), 1);
}

TEST(test_ichiprt2, Eql_INChI_Stereo_sp3_equal)
{
    // Setup two identical SP3 stereo objects
    INChI_Stereo s1 = {0}, s2 = {0};
    int num_centers = 2;
    AT_NUMB nNumber1[2] = {5, 6};
    S_CHAR t_parity1[2] = {1, 2};

    s1.nNumberOfStereoCenters = num_centers;
    s1.nNumber = nNumber1;
    s1.t_parity = t_parity1;

    s2.nNumberOfStereoCenters = num_centers;
    s2.nNumber = nNumber1;
    s2.t_parity = t_parity1;

    // Should be equal
    EXPECT_EQ(Eql_INChI_Stereo(&s1, EQL_SP3, &s2, EQL_SP3, 0), 1);
}

TEST(test_ichiprt2, Eql_INChI_Stereo_sp3_not_equal)
{
    // Setup two different SP3 stereo objects
    INChI_Stereo s1 = {0}, s2 = {0};
    int num_centers = 2;
    AT_NUMB nNumber1[2] = {5, 6};
    S_CHAR t_parity1[2] = {1, 2};

    AT_NUMB nNumber2[2] = {7, 8};
    S_CHAR t_parity2[2] = {2, 1};

    s1.nNumberOfStereoCenters = num_centers;
    s1.nNumber = nNumber1;
    s1.t_parity = t_parity1;

    s2.nNumberOfStereoCenters = num_centers;
    s2.nNumber = nNumber2;
    s2.t_parity = t_parity2;

    // Should not be equal
    EXPECT_EQ(Eql_INChI_Stereo(&s1, EQL_SP3, &s2, EQL_SP3, 0), 0);
}

