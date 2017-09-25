#ifndef CLION_TESTDRIVE_PRINT_VTABLE_H
#define CLION_TESTDRIVE_PRINT_VTABLE_H

#include <glib.h>
#include "print_typedef.h"

extern GHashTable *print_funcs;

typedef void (*print_fn_type)(struct textlist_s*);

void check_print_fn(print_fn_type pf);

#define print_hash_add(object, print_fn) { \
    check_print_fn(print_fn); \
    g_hash_table_insert(print_funcs, (object)->print, print_fn); \
}

void print_textlist_as_html(struct textlist_s *in);

#endif
