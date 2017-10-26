#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
#include <string.h>
//#include <stdlib.h>
#include "vendor/unity.h"
#include "print_vtable.h"
#include "n2t-assy/assy_symtable.h"
#include "n2t-assy/tests/assy_tests.h"


#define foo_frontend(x) _Generic((x), \
    int32_t: foo_int(x), \
    double: foo_dbl(x));

void foo_int(int32_t  x) {
    printf("foo_int %i\n", x);
}

void foo_dbl(double x) {
    printf("foo_dbl %f\n", x);
}

void test_hello_ben(void) {
    TEST_ASSERT_EQUAL_STRING("ben", "ben");
}


void blog4() {
    int32_t num, *pnum;
    pnum = &num;
    *pnum = 123;
    printf("  blog4() *pnum := %i\n", *pnum);
//
    float arr[10] = { 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6 }, *parr;
    parr = arr;
    parr = parr + 3;
    printf("  blog4() parr := %f\n", *parr);

    struct { wchar_t *name; float amount; } tag, *ptag;
    tag.amount = 59.99;
    ptag = &tag;
    ptag->name = "@vimjock ★";
    printf("  blog4() [name := %s] [amount := %f]\n", ptag->name, tag.amount);


    typedef struct { wchar_t * name, handle; double age, height; } person;

    person ben = { .name="Ben", .handle="vimjock", .age=34.6, .height=188.5 };
    printf("  blog4() %s [@%s] is %f years old", ben.name, ben.handle, ben.age);
}

void overloading_demo() {
    int a = 65;
    double b = 26.3;
    foo_frontend(a);
    foo_frontend(b);
}

// D Bernstein's simple hash algo
static unsigned int hash_str(wchar_t const *str) {
    uint32_t hash = 5381;
    wchar_t wc;
    while ((wc = *str++)) hash = hash * 33 + wc;
    return hash;


//    printf("fresh hash cookies 'hello' = %u\n", hash_str("hello"));
//    printf("fresh hash cookies 'world' = %u\n", hash_str("world"));
}


static void print_person_backend(struct person_s *in) {
    printf("\nName: %s\n", in->name);
    for (int i=0; i < in->len; i++)
        printf("-  Book author for: %s\n", in->books[i]);

}


int main(int argc, char *argv[]) {
//    UnityBegin("main.c");
//    RUN_TEST(test_hello_ben);
//    UnityEnd();

//    blog4();

//    overloading_demo();


    //vtable demo
//    struct person_s dennis = {
//        .name="Dennis Ritchie",
//        .books = (char*[]) { "The C Programming Language - 1978" },
//        .len = 1
//    };
//    print_person_frontend(&dennis);
//    printfn_vtable_add(&dennis, print_person_backend);
//    print_person_frontend(&dennis);
//
//    struct person_s rob = {
//         .name = "Rob Pike",
//        .books = (char*[]) { "The Unix Programming Environment - 1982", "The Practice of Programming - 1999" },
//        .len = 2
//    };
//    print_person_frontend(&rob);


//    assy_symtable symtable;
//    assy_symtable_new(&symtable);
//    symtable.add("SYM1", 1);
//    symtable.add("SYM2", 234);
//    symtable.add("SYM3", 1995);
//    printf("SYM3 = %i\n", symtable.get("SYM3"));


//    char *line = "// by Nisan and Schocken, MIT Press.";
//    char *line2 = "   D=M              // D = first number";
//    char *idx = strstr(line, "//");
//    if (idx) {
//        printf("%i\n", idx - line);
//    }


    // nand2tetris assembler unit tests
//    assy_tests_run();


    if (argc != 2) {
        printf("clion_testdrive input.asm\n");
        return 0;
    }

    char *infile = argv[1];
    assy_frontend_init(infile, "path/to/output/file");
    assy_frontend_first_pass();
    assy_frontend_second_pass();
}