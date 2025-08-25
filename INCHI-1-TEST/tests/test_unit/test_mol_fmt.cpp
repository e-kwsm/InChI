#include <gtest/gtest.h>

extern "C"
{
#include "../../../INCHI-1-SRC/INCHI_BASE/src/mol_fmt.h"
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
    //int MolfileReadField(void *data, int field_len, int data_type,  char **line_ptr)

    // SEG FAULT?   
    // EXPECT_EQ(MolfileReadField(NULL, 0, MOL_FMT_STRING_DATA, NULL), 0); // no data, no line pointer


    char data[5];

    char source_data[] = "ABCD 1234 56789";
    char *line_ptr = source_data;

    // MOL_FMT_STRING_DATA
    int ret_val = MolfileReadField(data, sizeof(data), MOL_FMT_STRING_DATA, &line_ptr);
    EXPECT_EQ(ret_val, 4); 
    EXPECT_STREQ(data, "ABCD");
    EXPECT_EQ(line_ptr, source_data + 5);

    //MOL_FMT_CHAR_INT_DATA -128 to 127
    // int char_ret_val = MolfileReadField(&char_data, sizeof(char_data), MOL_FMT_CHAR_INT_DATA, &line_ptr);
    // EXPECT_EQ(char_ret_val, 1);
    // EXPECT_EQ(char_data, '1');
    // EXPECT_EQ(line_ptr, source_data + 7);

    //MOL_FMT_SHORT_INT_DATA  -32,768 to 32,767
    // int short_data;
    // int short_ret_val = MolfileReadField(&short_data, sizeof(short_data), MOL_FMT_SHORT_INT_DATA, &line_ptr);
    // EXPECT_EQ(short_ret_val, 1);
    // EXPECT_EQ(short_data, 234);
    // EXPECT_EQ(line_ptr, source_data + 12);

    //MOL_FMT_LONG_INT_DATA -2,147,483,648 to 2,147,483,647
    //MOL_FMT_DOUBLE_DATA 
    //MOL_FMT_FLOAT_DATA
    //MOL_FMT_JUMP_TO_RIGHT
    //MOL_FMT_INT_DATA
}

