#include <gtest/gtest.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/inchi_api.h"
}

TEST(test_enhancedStereo, test_EnhancedStereochemistry_1)
{
    const char *molblock =
        "enhanc_stereo1									   \n"
        "  ACD/LABS08242216132D                            \n"
        "												   \n"
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

    char options[] = "-EnhancedStereochemistry";
    inchi_Output output;
    inchi_Output *poutput = &output;
    const char expected_inchi[] = "InChI=1S/C10H14BrCl7/c1-3(11)5(13)7(15)9(17)10(18)8(16)6(14)4(2)12/h3-10H,1-2H3/t3-,4-,5+,6-,7-,8-,9+,10-/m0/s1(3,5)2(6,8)(4)3(7,9)(10)";

    EXPECT_EQ(MakeINCHIFromMolfileText(molblock, options, poutput), 0);
    EXPECT_STREQ(poutput->szInChI, expected_inchi);

    poutput->szLog = nullptr;
    poutput->szMessage = nullptr;

    FreeINCHI(poutput);
}

TEST(test_enhancedStereo, test_EnhancedStereochemistry_2_mols)
{
    const char *molblock =
        "test_mol                                           \n"
        "  -INDIGO-01232613552D                             \n"
        "                                                   \n"
        "  0  0  0  0  0  0  0  0  0  0  0 V3000            \n"
        "M  V30 BEGIN CTAB                                  \n"
        "M  V30 COUNTS 36 34 0 0 0                          \n"
        "M  V30 BEGIN ATOM                                  \n"
        "M  V30 1 C 5.83301 -3.275 0.0 0 CFG=1              \n"
        "M  V30 2 C 4.96699 -2.775 0.0 0 CFG=1              \n"
        "M  V30 3 C 4.10096 -3.275 0.0 0 CFG=2              \n"
        "M  V30 4 C 3.23493 -2.775 0.0 0 CFG=1              \n"
        "M  V30 5 C 2.36891 -3.275 0.0 0 CFG=2              \n"
        "M  V30 6 C 1.50289 -2.775 0.0 0                    \n"
        "M  V30 7 Br 2.36891 -4.275 0.0 0                   \n"
        "M  V30 8 Cl 3.23493 -1.775 0.0 0                   \n"
        "M  V30 9 Cl 4.10096 -4.275 0.0 0                   \n"
        "M  V30 10 Cl 4.96699 -1.775 0.0 0                  \n"
        "M  V30 11 Cl 5.83301 -4.275 0.0 0                  \n"
        "M  V30 12 C 6.69904 -2.775 0.0 0 CFG=1             \n"
        "M  V30 13 C 7.56506 -3.275 0.0 0 CFG=1             \n"
        "M  V30 14 C 8.43109 -2.77501 0.0 0 CFG=2           \n"
        "M  V30 15 C 9.29711 -3.275 0.0 0                   \n"
        "M  V30 16 Cl 8.43109 -1.77501 0.0 0                \n"
        "M  V30 17 Cl 7.56506 -4.275 0.0 0                  \n"
        "M  V30 18 Cl 6.69904 -1.775 0.0 0                  \n"
        "M  V30 19 C 6.13302 -7.62502 0.0 0 CFG=2           \n"
        "M  V30 20 C 5.26698 -7.12498 0.0 0 CFG=1           \n"
        "M  V30 21 C 4.40101 -7.62502 0.0 0 CFG=2           \n"
        "M  V30 22 C 3.53496 -7.12498 0.0 0 CFG=1           \n"
        "M  V30 23 C 2.66891 -7.62502 0.0 0 CFG=2           \n"
        "M  V30 24 C 6.99899 -7.12498 0.0 0 CFG=2           \n"
        "M  V30 25 C 7.86504 -7.62502 0.0 0 CFG=2           \n"
        "M  V30 26 C 8.73109 -7.12498 0.0 0 CFG=2           \n"
        "M  V30 27 C 1.80295 -7.12498 0.0 0                 \n"
        "M  V30 28 Br 2.66891 -8.62501 0.0 0                \n"
        "M  V30 29 Cl 3.53496 -6.12499 0.0 0                \n"
        "M  V30 30 Cl 4.40101 -8.62501 0.0 0                \n"
        "M  V30 31 Cl 5.26698 -6.12499 0.0 0                \n"
        "M  V30 32 Cl 6.13302 -8.62501 0.0 0                \n"
        "M  V30 33 C 9.59705 -7.62502 0.0 0                 \n"
        "M  V30 34 Cl 8.73109 -6.12499 0.0 0                \n"
        "M  V30 35 Cl 7.86504 -8.62501 0.0 0                \n"
        "M  V30 36 Cl 6.99899 -6.12499 0.0 0                \n"
        "M  V30 END ATOM                                    \n"
        "M  V30 BEGIN BOND                                  \n"
        "M  V30 1 1 1 2                                     \n"
        "M  V30 2 1 1 11 CFG=3                              \n"
        "M  V30 3 1 1 12                                    \n"
        "M  V30 4 1 2 3                                     \n"
        "M  V30 5 1 2 10 CFG=1                              \n"
        "M  V30 6 1 3 4                                     \n"
        "M  V30 7 1 3 9 CFG=1                               \n"
        "M  V30 8 1 4 5                                     \n"
        "M  V30 9 1 4 8 CFG=1                               \n"
        "M  V30 10 1 5 6                                    \n"
        "M  V30 11 1 5 7 CFG=1                              \n"
        "M  V30 12 1 12 13                                  \n"
        "M  V30 13 1 12 18 CFG=3                            \n"
        "M  V30 14 1 13 14                                  \n"
        "M  V30 15 1 13 17 CFG=1                            \n"
        "M  V30 16 1 14 15                                  \n"
        "M  V30 17 1 14 16 CFG=1                            \n"
        "M  V30 18 1 19 20                                  \n"
        "M  V30 19 1 20 21                                  \n"
        "M  V30 20 1 21 22                                  \n"
        "M  V30 21 1 22 23                                  \n"
        "M  V30 22 1 19 24                                  \n"
        "M  V30 23 1 24 25                                  \n"
        "M  V30 24 1 25 26                                  \n"
        "M  V30 25 1 23 27                                  \n"
        "M  V30 26 1 23 28 CFG=1                            \n"
        "M  V30 27 1 22 29 CFG=1                            \n"
        "M  V30 28 1 21 30 CFG=1                            \n"
        "M  V30 29 1 20 31 CFG=1                            \n"
        "M  V30 30 1 19 32 CFG=3                            \n"
        "M  V30 31 1 26 33                                  \n"
        "M  V30 32 1 26 34 CFG=1                            \n"
        "M  V30 33 1 25 35 CFG=3                            \n"
        "M  V30 34 1 24 36 CFG=1                            \n"
        "M  V30 END BOND                                    \n"
        "M  V30 BEGIN COLLECTION                            \n"
        "M  V30 MDLV30/STERAC2 ATOMS=(1 1)                  \n"
        "M  V30 MDLV30/STERAC1 ATOMS=(2 2 3)                \n"
        "M  V30 MDLV30/STEABS ATOMS=(4 4 5 22 23)           \n"
        "M  V30 MDLV30/STEREL1 ATOMS=(2 12 13)              \n"
        "M  V30 MDLV30/STEREL2 ATOMS=(1 14)                 \n"
        "M  V30 MDLV30/STERAC4 ATOMS=(1 19)                 \n"
        "M  V30 MDLV30/STERAC3 ATOMS=(2 20 21)              \n"
        "M  V30 MDLV30/STEREL3 ATOMS=(2 24 25)              \n"
        "M  V30 MDLV30/STEREL4 ATOMS=(1 26)                 \n"
        "M  V30 END COLLECTION                              \n"
        "M  V30 END CTAB                                    \n"
        "M  END                                             \n";

    char options[] = "-EnhancedStereochemistry";
    inchi_Output output;
    inchi_Output *poutput = &output;
    const char expected_inchi[] = "InChI=1S/C10H14BrCl7/c1-3(11)5(13)7(15)9(17)10(18)8(16)6(14)4(2)12/h3-10H,1-2H3/t3-,4-,5+,6-,7-,8-,9+,10-/m0/s1(3,5)2(6,8)(4)3(7,9)(10)";

    EXPECT_EQ(MakeINCHIFromMolfileText(molblock, options, poutput), 0);
    EXPECT_STREQ(poutput->szInChI, expected_inchi);

    poutput->szLog = nullptr;
    poutput->szMessage = nullptr;

    FreeINCHI(poutput);
}

TEST(test_enhancedStereo, test_EnhancedStereochemistry_3_mols_molblock_wrong)
{
    const char *molblock =
        "my_test_mol                                      \n"
        "  -INDIGO-01232613442D                           \n"
        "                                                 \n"
        "  0  0  0  0  0  0  0  0  0  0  0 V3000          \n"
        "M  V30 BEGIN CTAB                                \n"
        "M  V30 COUNTS 36 34 0 0 0                        \n"
        "M  V30 BEGIN ATOM                                \n"
        "M  V30 1 C 5.83301 -3.275 0.0 0 CFG=1            \n"
        "M  V30 2 C 4.96699 -2.775 0.0 0 CFG=1            \n"
        "M  V30 3 C 4.10096 -3.275 0.0 0 CFG=2            \n"
        "M  V30 4 C 3.23493 -2.775 0.0 0 CFG=1            \n"
        "M  V30 5 C 2.36891 -3.275 0.0 0 CFG=2            \n"
        "M  V30 6 C 1.50289 -2.775 0.0 0                  \n"
        "M  V30 7 Br 2.36891 -4.275 0.0 0                 \n"
        "M  V30 8 Cl 3.23493 -1.775 0.0 0                 \n"
        "M  V30 9 Cl 4.10096 -4.275 0.0 0                 \n"
        "M  V30 10 Cl 4.96699 -1.775 0.0 0                \n"
        "M  V30 11 Cl 5.83301 -4.275 0.0 0                \n"
        "M  V30 12 C 6.69904 -2.775 0.0 0 CFG=1           \n"
        "M  V30 13 C 7.56506 -3.275 0.0 0 CFG=1           \n"
        "M  V30 14 C 8.43109 -2.77501 0.0 0 CFG=2         \n"
        "M  V30 15 C 9.29711 -3.275 0.0 0                 \n"
        "M  V30 16 Cl 8.43109 -1.77501 0.0 0              \n"
        "M  V30 17 Cl 7.56506 -4.275 0.0 0                \n"
        "M  V30 18 Cl 6.69904 -1.775 0.0 0                \n"
        "M  V30 19 C 6.13302 -7.62502 0.0 0 CFG=2         \n"
        "M  V30 20 C 5.26698 -7.12498 0.0 0 CFG=1         \n"
        "M  V30 21 C 4.40101 -7.62502 0.0 0 CFG=2         \n"
        "M  V30 22 C 3.53496 -7.12498 0.0 0 CFG=1         \n"
        "M  V30 23 C 2.66891 -7.62502 0.0 0 CFG=2         \n"
        "M  V30 24 C 6.99899 -7.12498 0.0 0 CFG=2         \n"
        "M  V30 25 C 7.86504 -7.62502 0.0 0 CFG=2         \n"
        "M  V30 26 C 8.73109 -7.12498 0.0 0 CFG=2         \n"
        "M  V30 27 C 1.80295 -7.12498 0.0 0               \n"
        "M  V30 28 Br 2.66891 -8.62501 0.0 0              \n"
        "M  V30 29 Cl 3.53496 -6.12499 0.0 0              \n"
        "M  V30 30 Cl 4.40101 -8.62501 0.0 0              \n"
        "M  V30 31 Cl 5.26698 -6.12499 0.0 0              \n"
        "M  V30 32 Cl 6.13302 -8.62501 0.0 0              \n"
        "M  V30 33 C 9.59705 -7.62502 0.0 0               \n"
        "M  V30 34 Cl 8.73109 -6.12499 0.0 0              \n"
        "M  V30 35 Cl 7.86504 -8.62501 0.0 0              \n"
        "M  V30 36 Cl 6.99899 -6.12499 0.0 0              \n"
        "M  V30 END ATOM                                  \n"
        "M  V30 BEGIN BOND                                \n"
        "M  V30 1 1 1 2                                   \n"
        "M  V30 2 1 1 11 CFG=3                            \n"
        "M  V30 3 1 1 12                                  \n"
        "M  V30 4 1 2 3                                   \n"
        "M  V30 5 1 2 10 CFG=1                            \n"
        "M  V30 6 1 3 4                                   \n"
        "M  V30 7 1 3 9 CFG=1                             \n"
        "M  V30 8 1 4 5                                   \n"
        "M  V30 9 1 4 8 CFG=1                             \n"
        "M  V30 10 1 5 6                                  \n"
        "M  V30 11 1 5 7 CFG=1                            \n"
        "M  V30 12 1 12 13                                \n"
        "M  V30 13 1 12 18 CFG=3                          \n"
        "M  V30 14 1 13 14                                \n"
        "M  V30 15 1 13 17 CFG=1                          \n"
        "M  V30 16 1 14 15                                \n"
        "M  V30 17 1 14 16 CFG=1                          \n"
        "M  V30 18 1 19 20                                \n"
        "M  V30 19 1 20 21                                \n"
        "M  V30 20 1 21 22                                \n"
        "M  V30 21 1 22 23                                \n"
        "M  V30 22 1 19 24                                \n"
        "M  V30 23 1 24 25                                \n"
        "M  V30 24 1 25 26                                \n"
        "M  V30 25 1 23 27                                \n"
        "M  V30 26 1 23 28 CFG=1                          \n"
        "M  V30 27 1 22 29 CFG=1                          \n"
        "M  V30 28 1 21 30 CFG=1                          \n"
        "M  V30 29 1 20 31 CFG=1                          \n"
        "M  V30 30 1 19 32 CFG=3                          \n"
        "M  V30 31 1 26 33                                \n"
        "M  V30 32 1 26 34 CFG=1                          \n"
        "M  V30 33 1 25 35 CFG=3                          \n"
        "M  V30 34 1 24 36 CFG=1                          \n"
        "M  V30 END BOND                                  \n"
        "M  V30 BEGIN COLLECTION                          \n"
        "M  V30 MDLV30/STERAC2 ATOMS=(2 1 19)             \n"
        "M  V30 MDLV30/STERAC1 ATOMS=(4 2 3 20 21)        \n"
        "M  V30 MDLV30/STEABS ATOMS=(4 4 5 22 23)         \n"
        "M  V30 MDLV30/STEREL1 ATOMS=(4 12 13 24 25)      \n"
        "M  V30 MDLV30/STEREL2 ATOMS=(2 14 26)            \n"
        "M  V30 END COLLECTION                            \n"
        "M  V30 END CTAB                                  \n"
        "M  END                                           \n";

    char options[] = "-EnhancedStereochemistry";
    inchi_Output output;
    inchi_Output *poutput = &output;
    const char expected_inchi[] = "InChI=1S/C10H14BrCl7/c1-3(11)5(13)7(15)9(17)10(18)8(16)6(14)4(2)12/h3-10H,1-2H3/t3-,4-,5+,6-,7-,8-,9+,10-/m0/s1(3,5)2(6,8)(4)3(7,9)(10)";

    // EXPECT_EQ(MakeINCHIFromMolfileText(molblock, options, poutput), 1);
    // EXPECT_STREQ(poutput->szInChI, expected_inchi);

    FreeINCHI(poutput);
}
