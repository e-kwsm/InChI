#include <gtest/gtest.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/strutil.h"
}

TEST(strutil_testing, test_SetConnectedComponentNumber)
{

    int num_atoms = 1;
    int test_component_number = 23;
    inp_ATOM *new_mol = CreateInpAtom(num_atoms);

    // int SetConnectedComponentNumber( inp_ATOM *at, int num_at, int component_number )
    EXPECT_EQ(SetConnectedComponentNumber(new_mol, 1, test_component_number), 0);

    for (int i = 0; i < num_atoms; i++)
    {
        EXPECT_EQ(new_mol[i].component, test_component_number);
    }
    FreeInpAtom(&new_mol);
}