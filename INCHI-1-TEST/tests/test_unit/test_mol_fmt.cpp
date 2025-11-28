#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/mol_fmt.h"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
}

TEST(mol_fmt_testing, test_MolfileStrnread)
{
    char dest[100];
    char source[] = "Hello World";
    char *first_space;
    int len = MolfileStrnread(dest, source, 100, &first_space);
    EXPECT_EQ(len, 11);
    EXPECT_STREQ(dest, "Hello World");
    EXPECT_EQ(first_space, dest + 11);
    EXPECT_EQ(first_space[0], '\0'); // null terminator

    len = MolfileStrnread(dest, source, 6, &first_space);
    EXPECT_EQ(len, 6);
    EXPECT_STREQ(dest, "Hello ");
    EXPECT_EQ(first_space, dest + 5);
    EXPECT_EQ(first_space[0], ' '); // space terminator
}

TEST(mol_fmt_testing, test_MolfileReadField)
{
    // int MolfileReadField(void *data, int field_len, int data_type,  char **line_ptr)

    // SEG FAULT?
    // EXPECT_EQ(MolfileReadField(NULL, 0, MOL_FMT_STRING_DATA, NULL), 0); // no data, no line pointer

    // MOL_FMT_STRING_DATA
    char data_str[5];
    char source_data1[] = "ABCD 1234 56789";
    char *line_ptr1 = source_data1;
    int ret_val_str = MolfileReadField(data_str, sizeof(data_str), MOL_FMT_STRING_DATA, &line_ptr1);
    EXPECT_EQ(ret_val_str, 4);
    EXPECT_STREQ(data_str, "ABCD");
    EXPECT_EQ(line_ptr1, source_data1 + 5);

    // MOL_FMT_CHAR_INT_DATA -128 to 127
    char data_char[2];
    char source_data2[] = "13";
    char *line_ptr2 = source_data2;
    int ret_val_char = MolfileReadField(data_char, sizeof(data_char), MOL_FMT_CHAR_INT_DATA, &line_ptr2);
    EXPECT_EQ(ret_val_char, 1);
    EXPECT_EQ(*data_char, static_cast<char>(13));
    EXPECT_EQ(line_ptr2, source_data2 + 2);

    // MOL_FMT_SHORT_INT_DATA  -32,768 to 32,767
    signed short data_s_int[10];
    char source_data3[] = "12345";
    char *line_ptr3 = source_data3;
    int ret_val_s_int = MolfileReadField(data_s_int, sizeof(data_s_int), MOL_FMT_SHORT_INT_DATA, &line_ptr3);
    EXPECT_EQ(ret_val_s_int, 1);
    EXPECT_EQ(*data_s_int, static_cast<signed short>(12345));
    EXPECT_EQ(line_ptr3, source_data3 + 5);

    // MOL_FMT_LONG_INT_DATA -2,147,483,648 to 2,147,483,647
    long data_long[1];
    char source_data4[] = "1234567";
    char *line_ptr4 = source_data4;
    int ret_val_long = MolfileReadField(data_long, sizeof(data_long), MOL_FMT_LONG_INT_DATA, &line_ptr4);
    EXPECT_EQ(ret_val_long, 1);
    EXPECT_EQ(*data_long, static_cast<long>(1234567));
    EXPECT_EQ(line_ptr4, source_data4 + 7);

    // MOL_FMT_DOUBLE_DATA
    double data_double[1];
    char source_data5[] = "123.4567";
    char *line_ptr5 = source_data5;
    int ret_val_double = MolfileReadField(data_double, sizeof(data_double), MOL_FMT_DOUBLE_DATA, &line_ptr5);
    EXPECT_EQ(ret_val_double, 1);
    EXPECT_EQ(*data_double, static_cast<double>(123.4567));
    EXPECT_EQ(line_ptr5, source_data5 + 8);

    // MOL_FMT_FLOAT_DATA
    float data_float[2];
    char source_data6[] = "12233.45";
    char *line_ptr6 = source_data6;
    int ret_val_float = MolfileReadField(data_float, sizeof(data_float), MOL_FMT_FLOAT_DATA, &line_ptr6);
    EXPECT_EQ(ret_val_float, 1);
    EXPECT_EQ(*data_float, static_cast<float>(12233.45));
    EXPECT_EQ(line_ptr6, source_data6 + 8);

    // MOL_FMT_JUMP_TO_RIGHT
    int jmp_idx = 9;
    char data_jmp[jmp_idx];
    char source_data7[] = "ABCD 1234 56789";
    char *line_ptr7 = source_data7;
    int ret_val_jmp = MolfileReadField(data_jmp, sizeof(data_jmp), MOL_FMT_JUMP_TO_RIGHT, &line_ptr7);
    EXPECT_EQ(ret_val_jmp, jmp_idx);
    EXPECT_EQ(line_ptr7, source_data7 + jmp_idx);

    // MOL_FMT_FLOAT_DATA
    float data_float_neg[2];
    char source_data8[] = "AVCD 23d";
    char *line_ptr8 = source_data8;
    int ret_val_float_neg = MolfileReadField(data_float_neg, sizeof(data_float_neg), MOL_FMT_FLOAT_DATA, &line_ptr8);
    EXPECT_EQ(ret_val_float_neg, -1);
    EXPECT_EQ(*data_float_neg, static_cast<float>(0));
    EXPECT_EQ(line_ptr8, source_data8 + 8);
}

TEST(mol_fmt_testing, test_MolfileExtractStrucNum)
{
    // long MolfileExtractStrucNum(MOL_FMT_HEADER_BLOCK *pHdr);

    MOL_FMT_HEADER_BLOCK hdr;
    memset(&hdr, 0, sizeof(hdr));

    /* valid header: "Structure #42" and line2 starts with INCHI_NAME and contains "SDfile Output" */
    strncpy(hdr.molname, "Structure #42", sizeof(hdr.molname) - 1);
    snprintf(hdr.line2, sizeof(hdr.line2), "%s SDfile Output", INCHI_NAME);

    long num = MolfileExtractStrucNum(&hdr);
    EXPECT_EQ(num, 42);

    //--------------------------
    memset(&hdr, 0, sizeof(hdr));

    /* correct "Structure #5" but line2 does not start with INCHI_NAME -> should return 0 */
    strncpy(hdr.molname, "Structure #5", sizeof(hdr.molname) - 1);
    strncpy(hdr.line2, "SomeOtherProducer SDfile Output", sizeof(hdr.line2) - 1);

    num = MolfileExtractStrucNum(&hdr);
    EXPECT_EQ(num, 0);

    //--------------------------
    memset(&hdr, 0, sizeof(hdr));

    /* non-numeric structure number should return 0 */
    strncpy(hdr.molname, "Structure #XX", sizeof(hdr.molname) - 1);
    snprintf(hdr.line2, sizeof(hdr.line2), "%s SDfile Output", INCHI_NAME);

    num = MolfileExtractStrucNum(&hdr);
    EXPECT_EQ(num, 0);

    //--------------------------
    memset(&hdr, 0, sizeof(hdr));

    /* non-numeric structure number should return 0 */
    strncpy(hdr.molname, "Structure #", sizeof(hdr.molname) - 1);
    snprintf(hdr.line2, sizeof(hdr.line2), "%s SDfile Output", INCHI_NAME);

    num = MolfileExtractStrucNum(&hdr);
    EXPECT_EQ(num, 0);

    //--------------------------
    memset(&hdr, 0, sizeof(hdr));

    /* non-numeric structure number should return 0 */
    strncpy(hdr.molname, "Strructure #12", sizeof(hdr.molname) - 1);
    snprintf(hdr.line2, sizeof(hdr.line2), "%s SDfile Output", INCHI_NAME);

    num = MolfileExtractStrucNum(&hdr);
    EXPECT_EQ(num, 0);
}

TEST(mol_fmt_testing, test_MolfileHasNoChemStruc)
{
    MOL_FMT_DATA mfdata;
    MOL_FMT_CTAB ctab;
    MOL_FMT_BOND bonds;
    MOL_FMT_ATOM *atoms;

    // Test NULL mfdata
    EXPECT_EQ(MolfileHasNoChemStruc(NULL), 1);

    // Initialize mfdata with NULL atoms
    memset(&mfdata, 0, sizeof(MOL_FMT_DATA));
    memset(&ctab, 0, sizeof(MOL_FMT_CTAB));
    mfdata.ctab = ctab;
    EXPECT_EQ(MolfileHasNoChemStruc(&mfdata), 1);

    // Test with n_atoms <= 0
    atoms = (MOL_FMT_ATOM *)calloc(1, sizeof(MOL_FMT_ATOM));
    ASSERT_NE(atoms, nullptr);
    mfdata.ctab.atoms = atoms;
    mfdata.ctab.n_atoms = 0;
    EXPECT_EQ(MolfileHasNoChemStruc(&mfdata), 1);
    mfdata.ctab.n_atoms = -1;
    EXPECT_EQ(MolfileHasNoChemStruc(&mfdata), 1);

    // Test with bonds declared but no bonds array
    mfdata.ctab.n_atoms = 1;
    mfdata.ctab.n_bonds = 1;
    mfdata.ctab.bonds = NULL;
    EXPECT_EQ(MolfileHasNoChemStruc(&mfdata), 1);

    // Test valid structure (has atoms and either no bonds or valid bonds array)
    mfdata.ctab.n_bonds = 0;
    EXPECT_EQ(MolfileHasNoChemStruc(&mfdata), 0);

    memset(&bonds, 0, sizeof(MOL_FMT_BOND));
    mfdata.ctab.n_bonds = 1;
    mfdata.ctab.bonds = &bonds;
    EXPECT_EQ(MolfileHasNoChemStruc(&mfdata), 0);

    // Clean up
    free(atoms);
}

TEST(mol_fmt_testing, test_FreeMolfileData)
{

    MOL_FMT_DATA *mfdata;

    MOL_FMT_HEADER_BLOCK *hdr;

    MOL_FMT_CTAB *ctab;
    MOL_FMT_BOND *bonds;
    MOL_FMT_ATOM *atoms;

    MOL_FMT_SGROUPS *sgroups;
    MOL_COORD *coords;
    MOL_FMT_v3000 *v3000;

    mfdata = (MOL_FMT_DATA *)calloc(1, sizeof(MOL_FMT_DATA));

    hdr = (MOL_FMT_HEADER_BLOCK *)calloc(1, sizeof(MOL_FMT_HEADER_BLOCK));

    ctab = (MOL_FMT_CTAB *)calloc(1, sizeof(MOL_FMT_CTAB));
    atoms = (MOL_FMT_ATOM *)calloc(1, sizeof(MOL_FMT_ATOM));
    bonds = (MOL_FMT_BOND *)calloc(1, sizeof(MOL_FMT_BOND));

    sgroups = (MOL_FMT_SGROUPS *)calloc(1, sizeof(MOL_FMT_SGROUPS));

    coords = (MOL_COORD *)calloc(1, sizeof(MOL_COORD));
    v3000 = (MOL_FMT_v3000 *)calloc(1, sizeof(MOL_FMT_v3000));

    mfdata->hdr = *hdr;

    mfdata->ctab = *ctab;
    mfdata->ctab.atoms = atoms;
    mfdata->ctab.bonds = bonds;

    mfdata->ctab.sgroups = *sgroups;
    mfdata->ctab.coords = coords;
    mfdata->ctab.v3000 = v3000;

    EXPECT_EQ(FreeMolfileData(NULL), nullptr);

    EXPECT_EQ(FreeMolfileData(mfdata), nullptr);
}

TEST(mol_fmt_testing, test_ReadMolfile_v2000)
{

    INCHI_IOSTREAM input_stream;

    const char *molblock =
        "caffeine                                                             \n"
        "  -OEChem-11272508282D                                               \n"
        "																	 \n"
        " 24 25  0     0  0  0  0  0  0999 V2000                              \n"
        "    3.7321    2.0000    0.0000 O   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    2.0000   -1.0000    0.0000 O   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    3.7321   -1.0000    0.0000 N   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    5.5443    0.8047    0.0000 N   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    2.8660    0.5000    0.0000 N   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    5.5443   -0.8047    0.0000 N   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    4.5981    0.5000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    4.5981   -0.5000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    3.7321    1.0000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    2.8660   -0.5000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    6.1279    0.0000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    3.7321   -2.0000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    5.8550    1.7553    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    2.0000    1.0000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    6.7479   -0.0000    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    3.1121   -2.0000    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    3.7321   -2.6200    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    4.3521   -2.0000    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    6.4443    1.5626    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    6.0476    2.3446    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    5.2656    1.9479    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    2.3100    1.5369    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    1.4631    1.3100    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "    1.6900    0.4631    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0\n"
        "  1  9  2  0  0  0  0                                                \n"
        "  2 10  2  0  0  0  0                                                \n"
        "  3  8  1  0  0  0  0                                                \n"
        "  3 10  1  0  0  0  0                                                \n"
        "  3 12  1  0  0  0  0                                                \n"
        "  4  7  1  0  0  0  0                                                \n"
        "  4 11  1  0  0  0  0                                                \n"
        "  4 13  1  0  0  0  0                                                \n"
        "  5  9  1  0  0  0  0                                                \n"
        "  5 10  1  0  0  0  0                                                \n"
        "  5 14  1  0  0  0  0                                                \n"
        "  6  8  1  0  0  0  0                                                \n"
        "  6 11  2  0  0  0  0                                                \n"
        "  7  8  2  0  0  0  0                                                \n"
        "  7  9  1  0  0  0  0                                                \n"
        " 11 15  1  0  0  0  0                                                \n"
        " 12 16  1  0  0  0  0                                                \n"
        " 12 17  1  0  0  0  0                                                \n"
        " 12 18  1  0  0  0  0                                                \n"
        " 13 19  1  0  0  0  0                                                \n"
        " 13 20  1  0  0  0  0                                                \n"
        " 13 21  1  0  0  0  0                                                \n"
        " 14 22  1  0  0  0  0                                                \n"
        " 14 23  1  0  0  0  0                                                \n"
        " 14 24  1  0  0  0  0                                                \n"
        "M  END                                                               \n";
    // "$$$$";

    inchi_ios_init(&input_stream, INCHI_IOS_TYPE_STRING, nullptr);
    inchi_ios_print_nodisplay(&input_stream, molblock);

    // MOL_FMT_DATA *ReadMolfile(INCHI_IOSTREAM *inp_file,
    //                         MOL_FMT_HEADER_BLOCK *OnlyHeaderBlock,
    //                         MOL_FMT_CTAB *OnlyCTab,
    //                         int bGetOrigCoord,
    //                         int treat_polymers,
    //                         int treat_NPZz,
    //                         char *pname,
    //                         int lname,
    //                         unsigned long *Id,
    //                         const char *pSdfLabel,
    //                         char *pSdfValue,
    //                         int *err,
    //                         char *pStrErr,
    //                         int bNoWarnings)

    INCHI_IOSTREAM *inp_file = &input_stream;
    MOL_FMT_HEADER_BLOCK *OnlyHeaderBlock = nullptr;
    MOL_FMT_CTAB *OnlyCTab = nullptr;
    int bGetOrigCoord = 0;
    int treat_polymers = 0;
    int treat_NPZz = 0;
    char *pname = nullptr;
    int lname = 0;
    unsigned long *Id = nullptr;
    const char *pSdfLabel = nullptr;
    char *pSdfValue = nullptr;
    int err = 0; // nullptr;
    char *pStrErr = nullptr;
    int bNoWarnings = 0;

    MOL_FMT_DATA *result = ReadMolfile(
        inp_file,
        OnlyHeaderBlock,
        OnlyCTab,
        bGetOrigCoord,
        treat_polymers,
        treat_NPZz,
        pname,
        lname,
        Id,
        pSdfLabel,
        pSdfValue,
        &err,
        pStrErr,
        bNoWarnings);

    EXPECT_STREQ(result->hdr.prog_name, "-OEChem-");
    EXPECT_STREQ(result->hdr.molname, "caffeine");

    EXPECT_EQ(result->ctab.n_atoms, 24);
    EXPECT_EQ(result->ctab.n_bonds, 25);
}

TEST(mol_fmt_testing, test_ReadMolfile_v3000)
{

    INCHI_IOSTREAM input_stream;

    const char *molblock =
        "caffeine_pc_v3.mol\n"
        "  ChemDraw11272515282D\n"
        "\n"
        "  0  0  0     0  0              0 V3000\n"
        "M  V30 BEGIN CTAB    \n"
        "M  V30 COUNTS 24 25 0 0 0\n"
        "M  V30 BEGIN ATOM     \n"
        "M  V30 1 O -0.309899 1.774158 0.000000 0\n"
        "M  V30 2 O -1.747434 -0.715655 0.000000 0\n"
        "M  V30 3 N -0.309899 -0.715655 0.000000 0\n"
        "M  V30 4 N 1.194114 0.782134 0.000000 0\n"
        "M  V30 5 N -1.028708 0.529252 0.000000 0\n"
        "M  V30 6 N 1.194114 -0.553568 0.000000 0\n"
        "M  V30 7 C 0.408827 0.529252 0.000000 0\n"
        "M  V30 8 C 0.408827 -0.300686 0.000000 0\n"
        "M  V30 9 C -0.309899 0.944221 0.000000 0\n"
        "M  V30 10 C -1.028708 -0.300686 0.000000 0\n"
        "M  V30 11 C 1.678466 0.114283 0.000000 0\n"
        "M  V30 12 C -0.309899 -1.545593 0.000000 0\n"
        "M  V30 13 C 1.451976 1.571072 0.000000 0\n"
        "M  V30 14 C -1.747434 0.944221 0.000000 0\n"
        "M  V30 15 H 2.193027 0.114283 0.000000 0\n"
        "M  V30 16 H -0.824461 -1.545593 0.000000 0\n"
        "M  V30 17 H -0.309899 -2.060154 0.000000 0\n"
        "M  V30 18 H 0.204662 -1.545593 0.000000 0\n"
        "M  V30 19 H 1.941058 1.411144 0.000000 0\n"
        "M  V30 20 H 1.611822 2.060154 0.000000 0\n"
        "M  V30 21 H 0.962811 1.730918 0.000000 0\n"
        "M  V30 22 H -1.490153 1.389814 0.000000 0\n"
        "M  V30 23 H -2.193027 1.201502 0.000000 0\n"
        "M  V30 24 H -2.004714 0.498627 0.000000 0\n"
        "M  V30 END ATOM\n"
        "M  V30 BEGIN BOND\n"
        "M  V30 1 2 1 9\n"
        "M  V30 2 2 2 10\n"
        "M  V30 3 1 3 8\n"
        "M  V30 4 1 3 10\n"
        "M  V30 5 1 3 12\n"
        "M  V30 6 1 4 7\n"
        "M  V30 7 1 4 11\n"
        "M  V30 8 1 4 13\n"
        "M  V30 9 1 5 9\n"
        "M  V30 10 1 5 10\n"
        "M  V30 11 1 5 14\n"
        "M  V30 12 1 6 8\n"
        "M  V30 13 2 6 11\n"
        "M  V30 14 2 7 8\n"
        "M  V30 15 1 7 9\n"
        "M  V30 16 1 11 15\n"
        "M  V30 17 1 12 16\n"
        "M  V30 18 1 12 17\n"
        "M  V30 19 1 12 18\n"
        "M  V30 20 1 13 19\n"
        "M  V30 21 1 13 20\n"
        "M  V30 22 1 13 21\n"
        "M  V30 23 1 14 22\n"
        "M  V30 24 1 14 23\n"
        "M  V30 25 1 14 24\n"
        "M  V30 END BOND   \n"
        "M  V30 END CTAB    \n"
        "M  END     \n";

    inchi_ios_init(&input_stream, INCHI_IOS_TYPE_STRING, nullptr);
    inchi_ios_print_nodisplay(&input_stream, molblock);

    // MOL_FMT_DATA *ReadMolfile(INCHI_IOSTREAM *inp_file,
    //                         MOL_FMT_HEADER_BLOCK *OnlyHeaderBlock,
    //                         MOL_FMT_CTAB *OnlyCTab,
    //                         int bGetOrigCoord,
    //                         int treat_polymers,
    //                         int treat_NPZz,
    //                         char *pname,
    //                         int lname,
    //                         unsigned long *Id,
    //                         const char *pSdfLabel,
    //                         char *pSdfValue,
    //                         int *err,
    //                         char *pStrErr,
    //                         int bNoWarnings)

    INCHI_IOSTREAM *inp_file = &input_stream;
    MOL_FMT_HEADER_BLOCK *OnlyHeaderBlock = nullptr;
    MOL_FMT_CTAB *OnlyCTab = nullptr;
    int bGetOrigCoord = 0;
    int treat_polymers = 0;
    int treat_NPZz = 0;
    char *pname = nullptr;
    int lname = 0;
    unsigned long *Id = nullptr;
    const char *pSdfLabel = nullptr;
    char *pSdfValue = nullptr;
    int err = 0; // nullptr;
    char *pStrErr = nullptr;
    int bNoWarnings = 0;

    MOL_FMT_DATA *result = ReadMolfile(
        inp_file,
        OnlyHeaderBlock,
        OnlyCTab,
        bGetOrigCoord,
        treat_polymers,
        treat_NPZz,
        pname,
        lname,
        Id,
        pSdfLabel,
        pSdfValue,
        &err,
        pStrErr,
        bNoWarnings);

    EXPECT_STREQ(result->hdr.prog_name, "ChemDraw");
    EXPECT_STREQ(result->hdr.molname, "caffeine_pc_v3.mol");

    EXPECT_EQ(result->ctab.n_atoms, 24);
    EXPECT_EQ(result->ctab.n_bonds, 25);
}

TEST(mol_fmt_testing, test_ReadMolfile_v3000_sgroup)
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

    // MOL_FMT_DATA *ReadMolfile(INCHI_IOSTREAM *inp_file,
    //                         MOL_FMT_HEADER_BLOCK *OnlyHeaderBlock,
    //                         MOL_FMT_CTAB *OnlyCTab,
    //                         int bGetOrigCoord,
    //                         int treat_polymers,
    //                         int treat_NPZz,
    //                         char *pname,
    //                         int lname,
    //                         unsigned long *Id,
    //                         const char *pSdfLabel,
    //                         char *pSdfValue,
    //                         int *err,
    //                         char *pStrErr,
    //                         int bNoWarnings)

    INCHI_IOSTREAM *inp_file = &input_stream;
    MOL_FMT_HEADER_BLOCK *OnlyHeaderBlock = nullptr;
    MOL_FMT_CTAB *OnlyCTab = nullptr;
    int bGetOrigCoord = 0;
    int treat_polymers = 0;
    int treat_NPZz = 0;
    char *pname = nullptr;
    int lname = 0;
    unsigned long *Id = nullptr;
    const char *pSdfLabel = nullptr;
    char *pSdfValue = nullptr;
    int err = 0; // nullptr;
    char *pStrErr = nullptr;
    int bNoWarnings = 0;

    MOL_FMT_DATA *result = ReadMolfile(
        inp_file,
        OnlyHeaderBlock,
        OnlyCTab,
        bGetOrigCoord,
        treat_polymers,
        treat_NPZz,
        pname,
        lname,
        Id,
        pSdfLabel,
        pSdfValue,
        &err,
        pStrErr,
        bNoWarnings);

    EXPECT_STREQ(result->hdr.prog_name, "ACD/LABS");
    EXPECT_STREQ(result->hdr.molname, "enhanc_stereo1");

    EXPECT_EQ(result->ctab.n_atoms, 18);
    EXPECT_EQ(result->ctab.n_bonds, 17);

    EXPECT_EQ(result->ctab.v3000->n_steabs, 1);

    // STEABS ATOMS=(2 4 5)
    EXPECT_EQ(result->ctab.v3000->steabs->lists[0][0], 1); // - not used
    EXPECT_EQ(result->ctab.v3000->steabs->lists[0][1], 2); // number of members in collection
    EXPECT_EQ(result->ctab.v3000->steabs->lists[0][2], 4); //  member atom numbers
    EXPECT_EQ(result->ctab.v3000->steabs->lists[0][3], 5); //  member atom numbers

    // STERAC2 ATOMS=(1 1)
    EXPECT_EQ(result->ctab.v3000->n_sterac, 2);

    EXPECT_EQ(result->ctab.v3000->sterac->lists[0][0], 2); // n from "STERACn" tag
    EXPECT_EQ(result->ctab.v3000->sterac->lists[0][1], 1); // number of members in collection
    EXPECT_EQ(result->ctab.v3000->sterac->lists[0][2], 1); // member atom numbers

    // STERAC1 ATOMS=(2 2 3)
    EXPECT_EQ(result->ctab.v3000->sterac->lists[1][0], 1); // STERAC1 ATOMS=(2 2 3)
    EXPECT_EQ(result->ctab.v3000->sterac->lists[1][1], 2); // number of members in collection
    EXPECT_EQ(result->ctab.v3000->sterac->lists[1][2], 2); // member atom numbers
    EXPECT_EQ(result->ctab.v3000->sterac->lists[1][3], 3); // member atom numbers

    EXPECT_EQ(result->ctab.v3000->n_sterel, 2);

    // STEREL1 ATOMS=(2 12 13)
    EXPECT_EQ(result->ctab.v3000->sterel->lists[0][0], 1);  // n from "STERELn" tag
    EXPECT_EQ(result->ctab.v3000->sterel->lists[0][1], 2);  // number of members in collection
    EXPECT_EQ(result->ctab.v3000->sterel->lists[0][2], 12); // member atom numbers
    EXPECT_EQ(result->ctab.v3000->sterel->lists[0][3], 13); // member atom numbers

    // STEREL2 ATOMS=(1 14)
    EXPECT_EQ(result->ctab.v3000->sterel->lists[1][0], 2);  // n from "STERELn" tag
    EXPECT_EQ(result->ctab.v3000->sterel->lists[1][1], 1);  // number of members in collection
    EXPECT_EQ(result->ctab.v3000->sterel->lists[1][2], 14); // member atom numbers
}
