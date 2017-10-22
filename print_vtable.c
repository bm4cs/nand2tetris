#include <stdio.h>
#include "print_vtable.h"

GHashTable *funcs_hash;

void check_print_fn(print_fn_type pf) { }

void print_person_frontend(struct person_s *in) {
    if (!funcs_hash) {
        funcs_hash = g_hash_table_new(g_direct_hash, g_direct_equal);
    }

    print_fn_type printfn = g_hash_table_lookup(funcs_hash, in->print);
    if (printfn) {
        printfn(in);
        return;
    }
    printf("No print implementation found in vtable...eek!\n");
}
