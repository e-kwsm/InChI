#include <gtest/gtest.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/util.h"
}

TEST(util_testing, test_get_chemical_symbols)
{

    char szElement[4];

    EXPECT_EQ(get_element_chemical_symbol(-4, szElement), -1);
    EXPECT_STREQ(szElement, "??");
    EXPECT_EQ(get_element_chemical_symbol(0, szElement), -1);
    EXPECT_STREQ(szElement, "??");
    EXPECT_EQ(get_element_chemical_symbol(1, szElement), 0);
    EXPECT_STREQ(szElement, "H");
    EXPECT_EQ(get_element_chemical_symbol(2, szElement), 0);
    EXPECT_STREQ(szElement, "He");
    EXPECT_EQ(get_element_chemical_symbol(5, szElement), 0);
    EXPECT_STREQ(szElement, "B");
    EXPECT_EQ(get_element_chemical_symbol(9, szElement), 0);
    EXPECT_STREQ(szElement, "F");
    EXPECT_EQ(get_element_chemical_symbol(45, szElement), 0);
    EXPECT_STREQ(szElement, "Rh");
    EXPECT_EQ(get_element_chemical_symbol(82, szElement), 0);
    EXPECT_STREQ(szElement, "Pb");
    EXPECT_EQ(get_element_chemical_symbol(5000, szElement), -1);
    EXPECT_STREQ(szElement, "??");
}

TEST(util_testing, test_get_element_or_pseudoelement_symbol)
{

    char szElement[4];

    EXPECT_EQ(get_element_or_pseudoelement_symbol(-4, szElement), -1);
    EXPECT_STREQ(szElement, "??");
    EXPECT_EQ(get_element_or_pseudoelement_symbol(0, szElement), -1);
    EXPECT_STREQ(szElement, "??");
    EXPECT_EQ(get_element_or_pseudoelement_symbol(1, szElement), 0);
    EXPECT_STREQ(szElement, "H");
    EXPECT_EQ(get_element_or_pseudoelement_symbol(119, szElement), 0);
    EXPECT_STREQ(szElement, "Zz");
    EXPECT_EQ(get_element_or_pseudoelement_symbol(120, szElement), 0);
    EXPECT_STREQ(szElement, "Zz");
    EXPECT_EQ(get_element_or_pseudoelement_symbol(255, szElement), -1);
    EXPECT_STREQ(szElement, "??");
    EXPECT_EQ(get_element_or_pseudoelement_symbol(45, szElement), 0);
    EXPECT_STREQ(szElement, "Rh");
    EXPECT_EQ(get_element_or_pseudoelement_symbol(5000, szElement), -1);
    EXPECT_STREQ(szElement, "??");
}

TEST(util_testing, test_get_periodic_table_number)
{

    char szElement[4];

    EXPECT_EQ(get_periodic_table_number("??"), 255);
    EXPECT_EQ(get_periodic_table_number("S"), 16);
    EXPECT_EQ(get_periodic_table_number("Ca"), 20);
    EXPECT_EQ(get_periodic_table_number("B"), 5);
    EXPECT_EQ(get_periodic_table_number("F"), 9);
    EXPECT_EQ(get_periodic_table_number("Rh"), 45);
    EXPECT_EQ(get_periodic_table_number("Zz"), 120);
}

TEST(util_testing, test_if_skip_add_H)
{

    EXPECT_EQ(if_skip_add_H(-1), 0);
    EXPECT_EQ(if_skip_add_H(5), 0);
    EXPECT_EQ(if_skip_add_H(54), 0);
    EXPECT_EQ(if_skip_add_H(25), 1);
    EXPECT_EQ(if_skip_add_H(57), 1);
    // EXPECT_EQ(if_skip_add_H(300), 0); --> SEG FAULT
}

TEST(util_testing, test_get_el_valence)
{
    // nPeriodicNum, charge, val_num
    EXPECT_EQ(get_el_valence(0, -3, 0), 0);
    EXPECT_EQ(get_el_valence(12, 5, 8), 0);
    EXPECT_EQ(get_el_valence(12, 1, 5), 0);

    EXPECT_EQ(get_el_valence(6, 0, 0), 4);
    EXPECT_EQ(get_el_valence(6, 1, 0), 3);
    EXPECT_EQ(get_el_valence(6, 1, 1), 0);

    EXPECT_EQ(get_el_valence(17, 0, 0), 1);
    EXPECT_EQ(get_el_valence(17, 0, 3), 7);

    EXPECT_EQ(get_el_valence(82, 0, 1), 4);
    EXPECT_EQ(get_el_valence(82, -2, 2), 6);
}

TEST(util_testing, test_get_atomic_mass)
{
    EXPECT_EQ(get_atomic_mass(""), 0);
    EXPECT_EQ(get_atomic_mass(" "), 0);
    EXPECT_EQ(get_atomic_mass("                      "), 0);
    EXPECT_EQ(get_atomic_mass("34sd"), 0);

    EXPECT_EQ(get_atomic_mass("H"), 1);
    EXPECT_EQ(get_atomic_mass("He"), 4);
    EXPECT_EQ(get_atomic_mass("Li"), 7);
    EXPECT_EQ(get_atomic_mass("Be"), 9);
    EXPECT_EQ(get_atomic_mass("B"), 11);
    EXPECT_EQ(get_atomic_mass("C"), 12);
    EXPECT_EQ(get_atomic_mass("N"), 14);
    EXPECT_EQ(get_atomic_mass("O"), 16);
    EXPECT_EQ(get_atomic_mass("F"), 19);
    EXPECT_EQ(get_atomic_mass("Ne"), 20);
    EXPECT_EQ(get_atomic_mass("Rh"), 103);
    EXPECT_EQ(get_atomic_mass("Pb"), 207);
}

TEST(util_testing, test_get_atomic_mass_from_elnum)
{
    EXPECT_EQ(get_atomic_mass_from_elnum(-1), 0);
    EXPECT_EQ(get_atomic_mass_from_elnum(0), 0);
    EXPECT_EQ(get_atomic_mass_from_elnum(1), 1);
    EXPECT_EQ(get_atomic_mass_from_elnum(2), 4);
    EXPECT_EQ(get_atomic_mass_from_elnum(3), 7);
    EXPECT_EQ(get_atomic_mass_from_elnum(4), 9);
    EXPECT_EQ(get_atomic_mass_from_elnum(5), 11);
    EXPECT_EQ(get_atomic_mass_from_elnum(6), 12);
    EXPECT_EQ(get_atomic_mass_from_elnum(7), 14);
    EXPECT_EQ(get_atomic_mass_from_elnum(8), 16);
    EXPECT_EQ(get_atomic_mass_from_elnum(9), 19);
    EXPECT_EQ(get_atomic_mass_from_elnum(10), 20);
    EXPECT_EQ(get_atomic_mass_from_elnum(11), 23);

    EXPECT_EQ(get_atomic_mass_from_elnum(57), 139);

    EXPECT_EQ(get_atomic_mass_from_elnum(23423423), 0);
}

TEST(util_testing, test_get_el_type)
{
    EXPECT_EQ(get_el_type(-1), 0);
    EXPECT_EQ(get_el_type(0), 0);
    EXPECT_EQ(get_el_type(1), 0);
    EXPECT_EQ(get_el_type(2), 0);
    EXPECT_EQ(get_el_type(3), 1);
    EXPECT_EQ(get_el_type(4), 1);
    EXPECT_EQ(get_el_type(5), 0);
    EXPECT_EQ(get_el_type(6), 0);
    EXPECT_EQ(get_el_type(7), 0);
    EXPECT_EQ(get_el_type(8), 0);
    EXPECT_EQ(get_el_type(9), 0);
    EXPECT_EQ(get_el_type(10), 0);
    EXPECT_EQ(get_el_type(11), 1);

    EXPECT_EQ(get_el_type(25), 3);

    EXPECT_EQ(get_el_type(57), 1);

    // EXPECT_EQ(get_el_type(23423423), 0); --> seg fault
}

TEST(util_testing, test_is_el_a_metal)
{
    EXPECT_EQ(is_el_a_metal(-1), false);
    EXPECT_EQ(is_el_a_metal(0), false);
    EXPECT_EQ(is_el_a_metal(1), false);
    EXPECT_EQ(is_el_a_metal(2), false);
    EXPECT_EQ(is_el_a_metal(3), true);
    EXPECT_EQ(is_el_a_metal(4), true);
    EXPECT_EQ(is_el_a_metal(5), false);
    EXPECT_EQ(is_el_a_metal(6), false);
    EXPECT_EQ(is_el_a_metal(7), false);
    EXPECT_EQ(is_el_a_metal(8), false);
    EXPECT_EQ(is_el_a_metal(9), false);
    EXPECT_EQ(is_el_a_metal(10), false);
    EXPECT_EQ(is_el_a_metal(11), true);

    EXPECT_EQ(is_el_a_metal(57), true);

    // EXPECT_EQ(is_el_a_metal(23423423), false); // --> seg fault
}

// ---------------------------

// lrtrim
TEST(util_testing, test_lrtrim)
{

    char test_string1[7] = " InChI";
    int nLen1 = 0;
    EXPECT_STREQ(lrtrim(test_string1, &nLen1), "InChI");
    EXPECT_EQ(nLen1, 5);

    char test_string2[9] = " InChI  ";
    int nLen2 = 0;
    EXPECT_STREQ(lrtrim(test_string2, &nLen2), "InChI");
    EXPECT_EQ(nLen2, 5);

    char test_string3[6] = "InChI";
    int nLen3 = 0;
    EXPECT_STREQ(lrtrim(test_string3, &nLen3), "InChI");
    EXPECT_EQ(nLen3, 5);
}

// ---------------------------

// extract_H_atoms( char *elname, S_CHAR num_iso_H[] )
TEST(util_testing, extract_H_atoms)
{
    S_CHAR num_iso_H[NUM_H_ISOTOPES] = {0};

    char elname[4] = "C";

    EXPECT_EQ(extract_H_atoms(elname, num_iso_H), 0);
    // printf("%s\n", num_iso_H);
    // EXPECT_STREQ(num_iso_H, "B");
}

TEST(util_testing, test_get_num_H)
{
    // const char *elname, int inp_num_H, S_CHAR *num_iso_H, int charge, int radical,
    // int chem_bonds_valence, int atom_input_valence, int bAliased, int bDoNotAddH, int bHasMetalNeighbor

    S_CHAR num_iso_H[NUM_H_ISOTOPES] = {0};

    EXPECT_EQ(get_num_H("C", 0, num_iso_H, 0, 0, 0, 0, 0, 0, 0), 4);
}

TEST(util_testing, test_get_unusual_el_valence)
{
    EXPECT_EQ(get_unusual_el_valence(0, 0, 0, 0, 0, 0), 0);
    EXPECT_EQ(get_unusual_el_valence(6, 0, 0, 4, 0, 0), 0);
    EXPECT_EQ(get_unusual_el_valence(6, 1, 0, 3, 1, 1), 4);
    EXPECT_EQ(get_unusual_el_valence(6, -1, 1, 3, 2, 2), 5);
    EXPECT_EQ(get_unusual_el_valence(17, -1, 0, 7, 2, 2), 9);
    EXPECT_EQ(get_unusual_el_valence(82, -2, 2, 6, 3, 3), 9);
}

TEST(util_testing, test_detect_unusual_el_valence)
{
    // nPeriodicNum, charge, radical, bonds_valence, num_H, num_bonds
    EXPECT_EQ(detect_unusual_el_valence(0, 0, 0, 0, 0, 0), 0);
    EXPECT_EQ(detect_unusual_el_valence(6, 0, 0, 4, 0, 0), 0);
    EXPECT_EQ(detect_unusual_el_valence(6, 1, 0, 3, 1, 1), 4);
    EXPECT_EQ(detect_unusual_el_valence(6, -1, 1, 3, 2, 2), 5);
    EXPECT_EQ(detect_unusual_el_valence(17, -1, 0, 7, 2, 2), 9);
    EXPECT_EQ(detect_unusual_el_valence(82, -2, 2, 6, 3, 3), 9);
}