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


    //MOL_FMT_STRING_DATA
    char data_str[5];
    char source_data1[] = "ABCD 1234 56789";
    char *line_ptr1 = source_data1;    
    int ret_val_str = MolfileReadField(data_str, sizeof(data_str), MOL_FMT_STRING_DATA, &line_ptr1);
    EXPECT_EQ(ret_val_str, 4); 
    EXPECT_STREQ(data_str, "ABCD");
    EXPECT_EQ(line_ptr1, source_data1 + 5);

    //MOL_FMT_CHAR_INT_DATA -128 to 127
    char data_char[2];
    char source_data2[] = "13";
    char *line_ptr2 = source_data2;
    int ret_val_char = MolfileReadField(data_char, sizeof(data_char), MOL_FMT_CHAR_INT_DATA, &line_ptr2);
    EXPECT_EQ(ret_val_char, 1);
    EXPECT_EQ(*data_char, static_cast<char>(13));
    EXPECT_EQ(line_ptr2, source_data2 + 2);

    //MOL_FMT_SHORT_INT_DATA  -32,768 to 32,767
    signed short data_s_int[10];
    char source_data3[] = "12345";
    char *line_ptr3 = source_data3;
    int ret_val_s_int = MolfileReadField(data_s_int, sizeof(data_s_int), MOL_FMT_SHORT_INT_DATA, &line_ptr3);
    EXPECT_EQ(ret_val_s_int, 1);
    EXPECT_EQ(*data_s_int, static_cast<signed short>(12345));
    EXPECT_EQ(line_ptr3, source_data3 + 5);

    //MOL_FMT_LONG_INT_DATA -2,147,483,648 to 2,147,483,647
    long data_long[1];
    char source_data4[] = "1234567";
    char *line_ptr4 = source_data4;
    int ret_val_long = MolfileReadField(data_long, sizeof(data_long), MOL_FMT_LONG_INT_DATA, &line_ptr4);
    EXPECT_EQ(ret_val_long, 1);
    EXPECT_EQ(*data_long, static_cast<long>(1234567));
    EXPECT_EQ(line_ptr4, source_data4 + 7);
    
    //MOL_FMT_DOUBLE_DATA
    double data_double[1];
    char source_data5[] = "123.4567";
    char *line_ptr5 = source_data5;
    int ret_val_double = MolfileReadField(data_double, sizeof(data_double), MOL_FMT_DOUBLE_DATA, &line_ptr5);
    EXPECT_EQ(ret_val_double, 1);
    EXPECT_EQ(*data_double, static_cast<double>(123.4567));
    EXPECT_EQ(line_ptr5, source_data5 + 8);

    //MOL_FMT_FLOAT_DATA
    float data_float[2];
    char source_data6[] = "12233.45";
    char *line_ptr6 = source_data6;
    int ret_val_float = MolfileReadField(data_float, sizeof(data_float), MOL_FMT_FLOAT_DATA, &line_ptr6);
    EXPECT_EQ(ret_val_float, 1);
    EXPECT_EQ(*data_float, static_cast<float>(12233.45));
    EXPECT_EQ(line_ptr6, source_data6 + 8);
    
    //MOL_FMT_JUMP_TO_RIGHT
    int jmp_idx = 9;
    char data_jmp[jmp_idx];
    char source_data7[] = "ABCD 1234 56789";
    char *line_ptr7 = source_data7;    
    int ret_val_jmp = MolfileReadField(data_jmp, sizeof(data_jmp), MOL_FMT_JUMP_TO_RIGHT, &line_ptr7);
    EXPECT_EQ(ret_val_jmp, jmp_idx);     
    EXPECT_EQ(line_ptr7, source_data7 + jmp_idx);    

    //MOL_FMT_FLOAT_DATA
    float data_float_neg[2];
    char source_data8[] = "AVCD 23d";
    char *line_ptr8 = source_data8;
    int ret_val_float_neg = MolfileReadField(data_float_neg, sizeof(data_float_neg), MOL_FMT_FLOAT_DATA, &line_ptr8);
    EXPECT_EQ(ret_val_float_neg, -1);
    EXPECT_EQ(*data_float_neg, static_cast<float>(0));
    EXPECT_EQ(line_ptr8, source_data8 + 8);
    

}

