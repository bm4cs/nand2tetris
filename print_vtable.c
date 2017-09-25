#include <stdio.h>
#include "print_vtable.h"

GHashTable *print_funcs;

void check_print_fn(print_fn_type pf) { }

void print_textlist_as_html(struct textlist_s *in) {
    if (!print_funcs) {
        print_funcs = g_hash_table_new(g_direct_hash, g_direct_equal);
    }

    print_fn_type printfn = g_hash_table_lookup(print_funcs, in->print);
    if (printfn) {
        printfn(in);
        return;
    }
    printf("No print implementation found in vtable...eek!\n");
}
