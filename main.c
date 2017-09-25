#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
//#include <stdlib.h>
#include "vendor/unity.h"
#include "print_vtable.h"


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


static void printy_textlist(struct textlist_s *in) {
    printf("<title>%s</title>\n", in->title);
    for (int i=0; i < in->len; i++)
        printf("  <li>%s</li>\n", in->items[i]);
}


int main() {
//    UnityBegin("main.c");
//    RUN_TEST(test_hello_ben);
//    UnityEnd();

//    blog4();

//    overloading_demo();


    struct textlist_s bens_books = {
        .title="Ben's awesome coding books",
        .items = (char*[]) { "Code Complete", "C Pocket Reference", "The Pragmatic Programmer" },
        .len = 3
    };
    print_textlist_as_html(&bens_books);
    print_hash_add(&bens_books, printy_textlist);
    print_textlist_as_html(&bens_books);

    return 0;
}