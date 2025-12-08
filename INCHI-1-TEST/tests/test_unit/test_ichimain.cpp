#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichitime.h"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichi_io.h"
#include "../../../INCHI-1-SRC/INCHI_BASE/src/ichimain.h"
}

static char* make_arg(const char* s) {
    size_t len = strlen(s) + 1;
    char* p = (char*)malloc(len);
    memcpy(p, s, len);
    return p;
}

// TEST(ichimain_testing, test_ProcessSingleInputFile)
// {


//     const char *test_file_2mols = "/workspaces/InChI/INCHI-1-TEST/tests/test_unit/fixtures/test_mol2.sdf";

//     char tmpl[] = "/workspaces/InChI/INCHI-1-TEST/tests/test_unit/fixtures/inchi_mol_test_XXXXXX";
//     char *tmpd = mkdtemp(tmpl);
//     ASSERT_NE(tmpd, nullptr);

//     std::string dst_path = std::string(tmpd) + "/caffeine.mol";
//     std::ifstream src(test_file_caffeine, std::ios::binary);
//     ASSERT_TRUE(src.is_open());
//     std::ofstream dst(dst_path, std::ios::binary);
//     ASSERT_TRUE(dst.is_open());
//     dst << src.rdbuf();
//     src.close();
//     dst.close();

//     int argc = 2;
//     char *a0 = make_arg("test_ichimain");
//     char *a1 = make_arg(dst_path.c_str());
//     char* argv[] = { a0, a1 };



// }

TEST(ichimain_testing, test_ProcessSingleInputFile_caffeine)
{

    const char *filename_caffeine = "caffeine.mol";

    const char *path_fixtures = "/workspaces/InChI/INCHI-1-TEST/tests/test_unit/fixtures";
    char tmpl[] = "/workspaces/InChI/INCHI-1-TEST/tests/test_unit/fixtures/inchi_mol_test_XXXXXX";
    char *tmpd = mkdtemp(tmpl);
    ASSERT_NE(tmpd, nullptr);

    std::string src_path = std::string(path_fixtures) + "/" + filename_caffeine;
    std::string dst_path = std::string(tmpd) + "/" + filename_caffeine;
    std::ifstream src(src_path, std::ios::binary);
    ASSERT_TRUE(src.is_open());
    std::ofstream dst(dst_path, std::ios::binary);
    ASSERT_TRUE(dst.is_open());
    dst << src.rdbuf();
    src.close();
    dst.close();

    int argc = 2;
    char *a0 = make_arg("test_ichimain");
    char *a1 = make_arg(dst_path.c_str());
    char* argv[] = { a0, a1 };

    // int ProcessSingleInputFile(int argc, char* argv[])

    int result = ProcessSingleInputFile(argc, argv);

    // Assert the expected result
    EXPECT_EQ(result, 0);

    free(a0);
    free(a1);

    std::string out_txt = dst_path + ".txt";
    std::string out_log = dst_path + ".log";
    std::string out_prb = dst_path + ".prb";

    struct stat st;
    // check existence and non-zero size
    ASSERT_EQ(stat(out_txt.c_str(), &st), 0);
    EXPECT_GT(st.st_size, 0);
    ASSERT_EQ(stat(out_log.c_str(), &st), 0);
    EXPECT_GT(st.st_size, 0);
    ASSERT_EQ(stat(out_prb.c_str(), &st), 0);
    // EXPECT_GT(st.st_size, 0);
    EXPECT_EQ(st.st_size, 0);

    std::ifstream txt_in(out_txt);
    ASSERT_TRUE(txt_in.is_open());
    std::string line;
    std::string found_inchi;
    while (std::getline(txt_in, line)) {
        // trim leading/trailing whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue;
        size_t end = line.find_last_not_of(" \t\r\n");
        std::string trimmed = line.substr(start, end - start + 1);
        if (trimmed.rfind("InChI=", 0) == 0) {
            found_inchi = trimmed;
            break;
        }
    }
    txt_in.close();

    const std::string expected_inchi = "InChI=1S/C8H10N4O2/c1-10-4-9-6-5(10)7(13)12(3)8(14)11(6)2/h4H,1-3H3";
    ASSERT_FALSE(found_inchi.empty());
    EXPECT_EQ(found_inchi, expected_inchi);

    // cleanup
    unlink(out_txt.c_str());
    unlink(out_log.c_str());
    unlink(out_prb.c_str());
    unlink(dst_path.c_str());
    rmdir(tmpd);
}
TEST(ichimain_testing, test_ProcessSingleInputFile_2mols_sdf)
{

    const char *filename_2mols = "test_mols_2.sdf";

    const char *path_fixtures = "/workspaces/InChI/INCHI-1-TEST/tests/test_unit/fixtures";
    char tmpl[] = "/workspaces/InChI/INCHI-1-TEST/tests/test_unit/fixtures/inchi_mol_test_XXXXXX";
    char *tmpd = mkdtemp(tmpl);
    ASSERT_NE(tmpd, nullptr);

    std::string src_path = std::string(path_fixtures) + "/" + filename_2mols;
    std::string dst_path = std::string(tmpd) + "/" + filename_2mols;
    std::ifstream src(src_path, std::ios::binary);
    ASSERT_TRUE(src.is_open());
    std::ofstream dst(dst_path, std::ios::binary);
    ASSERT_TRUE(dst.is_open());
    dst << src.rdbuf();
    src.close();
    dst.close();

    int argc = 2;
    char *a0 = make_arg("test_ichimain");
    char *a1 = make_arg(dst_path.c_str());
    char* argv[] = { a0, a1 };

    // int ProcessSingleInputFile(int argc, char* argv[])

    int result = ProcessSingleInputFile(argc, argv);

    // Assert the expected result
    EXPECT_EQ(result, 0);

    free(a0);
    free(a1);

    std::string out_txt = dst_path + ".txt";
    std::string out_log = dst_path + ".log";
    std::string out_prb = dst_path + ".prb";

    struct stat st;
    // check existence and non-zero size
    ASSERT_EQ(stat(out_txt.c_str(), &st), 0);
    EXPECT_GT(st.st_size, 0);
    ASSERT_EQ(stat(out_log.c_str(), &st), 0);
    EXPECT_GT(st.st_size, 0);
    ASSERT_EQ(stat(out_prb.c_str(), &st), 0);
    // EXPECT_GT(st.st_size, 0);
    EXPECT_EQ(st.st_size, 0);

    std::ifstream txt_in(out_txt);
    ASSERT_TRUE(txt_in.is_open());
    std::string line;
    std::vector<std::string> found_inchis;
    while (std::getline(txt_in, line)) {
        // trim leading/trailing whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue;
        size_t end = line.find_last_not_of(" \t\r\n");
        std::string trimmed = line.substr(start, end - start + 1);
        if (trimmed.rfind("InChI=", 0) == 0) {
            found_inchis.push_back(trimmed);
        }
    }
    txt_in.close();

    std::vector<std::string> expected_inchis = {
        "InChI=1S/C66H75Cl2N9O24/c1-23(2)12-34(71-5)58(88)76-49-51(83)26-7-10-38(32(67)14-26)97-40-16-28-17-41(55(40)101-65-56(54(86)53(85)42(22-78)99-65)100-44-21-66(4,70)57(87)24(3)96-44)98-39-11-8-27(15-33(39)68)52(84)50-63(93)75-48(64(94)95)31-18-29(79)19-37(81)45(31)30-13-25(6-9-36(30)80)46(60(90)77-50)74-61(91)47(28)73-59(89)35(20-43(69)82)72-62(49)92/h6-11,13-19,23-24,34-35,42,44,46-54,56-57,65,71,78-81,83-87H,12,20-22,70H2,1-5H3,(H2,69,82)(H,72,92)(H,73,89)(H,74,91)(H,75,93)(H,76,88)(H,77,90)(H,94,95)/t24-,34+,35-,42?,44-,46+,47+,48-,49+,50-,51+,52+,53+,54-,56+,57+,65-,66-/m0/s1",
        "InChI=1S/C8H10N4O2/c1-10-4-9-6-5(10)7(13)12(3)8(14)11(6)2/h4H,1-3H3"
    };

    ASSERT_EQ(found_inchis.size(), expected_inchis.size());
    for (size_t i = 0; i < expected_inchis.size(); ++i) {
        EXPECT_EQ(found_inchis[i], expected_inchis[i]);
    }

    // cleanup
    unlink(out_txt.c_str());
    unlink(out_log.c_str());
    unlink(out_prb.c_str());
    unlink(dst_path.c_str());
    rmdir(tmpd);
}

TEST(ichimain_testing, test_GetTheNextRecordOfInputFile)
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

    // int GetTheNextRecordOfInputFile( struct tagINCHI_CLOCK *ic,
    //                              STRUCT_DATA *sd, INPUT_PARMS *ip,
    //                              char *szTitle,
    //                              INCHI_IOSTREAM *inp_file,
    //                              INCHI_IOSTREAM *plog,
    //                              INCHI_IOSTREAM *pout,
    //                              INCHI_IOSTREAM *pprb,
    //                              ORIG_ATOM_DATA *orig_inp_data,
    //                              long *num_inp,
    //                              STRUCT_FPTRS *pStructPtrs,
    //                              int *nRet,
    //                              int *have_err_in_GetOneStructure,
    //                              long *num_err,
    //                              int output_error_inchi );

    INCHI_CLOCK ic = {};
    memset(&ic, 0, sizeof(ic));

    STRUCT_DATA *sd = new STRUCT_DATA;
    INPUT_PARMS *ip = new INPUT_PARMS;

    char *szTitle;
    INCHI_IOSTREAM *inp_file;
    INCHI_IOSTREAM *plog = new INCHI_IOSTREAM;
    INCHI_IOSTREAM *pout = new INCHI_IOSTREAM;
    INCHI_IOSTREAM *pprb = new INCHI_IOSTREAM;
    ORIG_ATOM_DATA orig_at_data = {};
    long *num_inp = new long(0);

    STRUCT_FPTRS *pStructPtrs = NULL;

    int *nRet = 0;
    int *have_err_in_GetOneStructure = 0;
    long *num_err;
    int output_error_inchi;


    memset(ip, 0, sizeof(*ip));
    ip->last_struct_number = 1;
    ip->nInputType = INPUT_MOLFILE;

    inchi_ios_init(pout, INCHI_IOS_TYPE_STRING, nullptr);
    inchi_ios_init(plog, INCHI_IOS_TYPE_STRING, stdout);
    inchi_ios_init(pprb, INCHI_IOS_TYPE_STRING, nullptr);

    // PrintInputParms(plog, ip);
    // inchi_ios_flush2(plog, stderr);

    // int ret = GetTheNextRecordOfInputFile(
    //     &ic,
    //     sd,
    //     ip,
    //     szTitle,
    //     &input_stream,
    //     plog,
    //     pout,
    //     pprb,
    //     &orig_at_data,
    //     num_inp,
    //     pStructPtrs,
    //     nRet,
    //     have_err_in_GetOneStructure,
    //     num_err,
    //     output_error_inchi);

    // EXPECT_EQ(ret, DO_NEXT_STEP);

    inchi_ios_free_str(&input_stream);
    FreeOrigAtData(&orig_at_data);
}
