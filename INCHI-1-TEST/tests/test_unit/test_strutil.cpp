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

/* (NaumanUllahKhan :: @nnuk)
* Test to validate the disconnection or non-disconnection of bond 
* between a Metal and a Non-Metal atom.
*/
TEST(strutil_testing, test_MolecularInorganicsPreprocessing) 
{
    INPUT_PARMS ip;
    memset(&ip, 0, sizeof(ip));
    ip.bMolecularInorganics = true;
    ip.bMolecularInorganicsReconnectedInChI = false;
    
    ORIG_ATOM_DATA orig_at_data;
    memset(&orig_at_data, 0, sizeof(orig_at_data));
    
    inp_ATOM atoms[3];
    AT_NUMB nOldCompNumber[3] = {0};
    
    /* Initialize all atoms */
    for (int i = 0; i < 3; i++) 
    {
        memset(&atoms[i], 0, sizeof(inp_ATOM));
        atoms[i].num_iso_H[0] = 0;
        atoms[i].num_iso_H[1] = 0; 
        atoms[i].num_iso_H[2] = 0;
        atoms[i].num_H = 0;
        atoms[i].charge = 0;
        atoms[i].chem_bonds_valence = 0;
        atoms[i].valence = 0;
        atoms[i].el_number = 0;
        atoms[i].orig_at_number = i + 1;
    }
    
    /* Central Metal atom (Iron) */
    atoms[0].el_number = 26;
    atoms[0].valence = 2;
    atoms[0].chem_bonds_valence = 2;
    strcpy(atoms[0].elname, "Fe");
    atoms[0].neighbor[0] = 1;
    atoms[0].neighbor[1] = 2;
    atoms[0].bond_type[0] = 1;
    atoms[0].bond_type[1] = 1;
    
    /* Non-Metal atom (Chlorine) */
    atoms[1].el_number = 17;
    atoms[1].valence = 1;
    atoms[1].chem_bonds_valence = 1;
    strcpy(atoms[1].elname, "Cl");
    atoms[1].neighbor[0] = 0;
    atoms[1].bond_type[0] = 1;
    
    /* Non-Metal atom (Fluorine) */
    atoms[2].el_number = 9;
    atoms[2].valence = 1;
    atoms[2].chem_bonds_valence = 1;
    strcpy(atoms[2].elname, "F");
    atoms[2].neighbor[0] = 0;
    atoms[2].bond_type[0] = 1;
    
    orig_at_data.at = atoms;
    orig_at_data.num_inp_atoms = 3;
    orig_at_data.nOldCompNumber = nOldCompNumber;
    
    int result = MolecularInorganicsPreprocessing(&orig_at_data, &ip);
    
    /* Should disconnect only 1 bond, Fe-F (not Fe-Cl) */
    EXPECT_EQ(result, 1);
    EXPECT_TRUE(ip.bMolecularInorganicsReconnectedInChI);

    /* Charges: Fe -> +1, Cl -> unchanged, F -> -1 */
    EXPECT_EQ(atoms[0].charge, 1);
    EXPECT_EQ(atoms[1].charge, 0);
    EXPECT_EQ(atoms[2].charge, -1);
}