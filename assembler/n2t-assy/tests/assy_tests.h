#ifndef ASSY_TESTS_H
#define ASSY_TESTS_H

#include <unity.h>
#include <stdbool.h>
#include "../assy_symtable.h"
#include "../assy_translator.h"
#include "../assy_parser.h"
#include "../assy_frontend.h"

void test_symtable(void) {
    assy_symtable symtab;
    assy_symtable_new(&symtab);
    symtab.add("SYM1", 1);
    symtab.add("SYM2", 234);
    symtab.add("SYM3", 1995);
    TEST_ASSERT_EQUAL_INT32(1995, symtab.get("SYM3"));
    TEST_ASSERT_TRUE(symtab.contains("SYM1"));
    TEST_ASSERT_TRUE(symtab.contains("SYM2"));
    TEST_ASSERT_TRUE(symtab.contains("SYM3"));
    TEST_ASSERT_FALSE(symtab.contains("FOO"));
    TEST_ASSERT_TRUE(symtab.contains("SCREEN"));
    TEST_ASSERT_EQUAL_INT32(0, symtab.get("R0"));
}

void test_translator(void) {
    // compute bits
    TEST_ASSERT_EQUAL_STRING("0010101", assy_translator_get_compute_bits("D|A"));
    TEST_ASSERT_EQUAL_STRING("1110011", assy_translator_get_compute_bits("-M"));

    // dest bits
    TEST_ASSERT_EQUAL_STRING("110", assy_translator_get_destination_bits("AD"));
    TEST_ASSERT_EQUAL_STRING("000", assy_translator_get_destination_bits(NULL));

    // jump bits
    TEST_ASSERT_EQUAL_STRING("111", assy_translator_get_jump_bits("JMP"));
    TEST_ASSERT_EQUAL_STRING("010", assy_translator_get_jump_bits("JEQ"));
    TEST_ASSERT_EQUAL_STRING("000", assy_translator_get_jump_bits(NULL));

    char *bitmap = assy_translator_get_a_instruction_bits(10);
    TEST_ASSERT_EQUAL_STRING("0000000000001010", bitmap);

    TEST_ASSERT_EQUAL_STRING("1110101010000000", assy_translator_get_c_instruction_bits("0", NULL, NULL));
}

void test_parser(void) {
    assy_parser parser;
    assy_parser_new(&parser, "../n2t-assy/tests/ben.asm");

    parser.read_next(); //D=D+A
    TEST_ASSERT_EQUAL(INSTRUCTION_TYPE_C, parser.get_instruction_type());
    TEST_ASSERT_EQUAL_STRING("D", parser.get_dest());
    TEST_ASSERT_EQUAL_STRING("D+A", parser.get_comp());
    TEST_ASSERT_NULL(parser.get_jump());

    parser.read_next(); //0;JMP
    TEST_ASSERT_EQUAL(INSTRUCTION_TYPE_C, parser.get_instruction_type());
    TEST_ASSERT_EQUAL_STRING("0", parser.get_comp());
    TEST_ASSERT_EQUAL_STRING("JMP", parser.get_jump());
    TEST_ASSERT_NULL(parser.get_dest());

    parser.read_next(); //@12
    TEST_ASSERT_EQUAL(INSTRUCTION_TYPE_A, parser.get_instruction_type());
    TEST_ASSERT_EQUAL_STRING("12", parser.get_symbol());

    parser.read_next(); //(FOO)
    TEST_ASSERT_EQUAL(INSTRUCTION_TYPE_L, parser.get_instruction_type());
    TEST_ASSERT_EQUAL_STRING("FOO", parser.get_symbol());

    parser.read_next(); //   D=M              // D = first number
    TEST_ASSERT_EQUAL(INSTRUCTION_TYPE_C, parser.get_instruction_type());
    TEST_ASSERT_EQUAL_STRING("D", parser.get_dest());
    TEST_ASSERT_EQUAL_STRING("M", parser.get_comp());
    TEST_ASSERT_NULL(parser.get_jump());
}

void test_frontend(void) {
    assy_frontend_init("../n2t-assy/tests/ben.asm", "../n2t-assy/tests/ben.hack");
    assy_frontend_first_pass();
    TEST_ASSERT_TRUE(assy_frontend_symtab.contains("FOO"));
    TEST_ASSERT_EQUAL_INT32(3, assy_frontend_symtab.get("FOO"));
    assy_frontend_second_pass();
}


void test_frontend_two(void) {
    assy_frontend_init("../n2t-assy/tests/max.asm", "../n2t-assy/tests/add.hack");
    assy_frontend_first_pass();
    assy_frontend_second_pass();
}


static void assy_tests_run() {
    UnityBegin("assy_tests.h");
    RUN_TEST(test_symtable);
    RUN_TEST(test_translator);
    RUN_TEST(test_parser);
    RUN_TEST(test_frontend);
    RUN_TEST(test_frontend_two);
    UnityEnd();
}

#endif
