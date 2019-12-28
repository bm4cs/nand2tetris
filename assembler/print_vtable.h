#ifndef CLION_TESTDRIVE_PRINT_VTABLE_H
#define CLION_TESTDRIVE_PRINT_VTABLE_H

#include <glib.h>
#include "person_s.h"

extern GHashTable *funcs_hash;

typedef void (*print_fn_type)(struct person_s*);

void check_print_fn(print_fn_type pf);

#define printfn_vtable_add(object, fn) { \
    check_print_fn(fn); \
    g_hash_table_insert(funcs_hash, (object)->print, fn); \
}

void print_person_frontend(struct person_s *in);

#endif
