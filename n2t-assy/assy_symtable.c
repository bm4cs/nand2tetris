#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include "assy_symtable.h"

#define BASE_RAM_ADDRESS_FOR_VARIABLES 16

GHashTable *assy_symtable_hash;
int32_t assy_symtable_next_available_variable_addr;

_Bool assy_symtable_contains(char *name) {
    if (assy_symtable_hash) {
        return g_hash_table_contains(assy_symtable_hash, name);
    }
    return false;
}

void assy_symtable_add(char *name, int32_t address) {
    if (!assy_symtable_hash) {
        assy_symtable_hash = g_hash_table_new(g_str_hash, g_str_equal);
        assy_symtable_load_predefined();
        assy_symtable_next_available_variable_addr = BASE_RAM_ADDRESS_FOR_VARIABLES;
    }

    if (assy_symtable_contains(name)) {
        g_hash_table_replace(assy_symtable_hash, name, address);
        return;
    }

    g_hash_table_insert(assy_symtable_hash, name, address);
}

int32_t assy_symtable_add_variable(char *name) {
    assy_symtable_add(name, assy_symtable_next_available_variable_addr);
    return assy_symtable_next_available_variable_addr++;
}

int32_t *assy_symtable_get(char *name) {
    if (!assy_symtable_hash) {
        return -1;
    }

    int32_t addr = g_hash_table_lookup(assy_symtable_hash, name);
    return addr;
}

void assy_symtable_load_predefined() {
    assy_symtable_add("SP", 0);
    assy_symtable_add("LCL", 1);
    assy_symtable_add("ARG", 2);
    assy_symtable_add("THIS", 3);
    assy_symtable_add("THAT", 4);
    assy_symtable_add("R0", 0);
    assy_symtable_add("R1", 1);
    assy_symtable_add("R2", 2);
    assy_symtable_add("R3", 3);
    assy_symtable_add("R4", 4);
    assy_symtable_add("R5", 5);
    assy_symtable_add("R6", 6);
    assy_symtable_add("R7", 7);
    assy_symtable_add("R8", 8);
    assy_symtable_add("R9", 9);
    assy_symtable_add("R10", 10);
    assy_symtable_add("R11", 11);
    assy_symtable_add("R12", 12);
    assy_symtable_add("R13", 13);
    assy_symtable_add("R14", 14);
    assy_symtable_add("R15", 15);
    assy_symtable_add("SCREEN", 16384);
    assy_symtable_add("KBD", 24576);
}

void assy_symtable_debug() {
    printf("hash size %i\n", g_hash_table_size(assy_symtable_hash));
    GList *list = g_hash_table_get_keys(assy_symtable_hash);
    if (list) {
        GList *l;
        for (l = list; l != NULL; l = l->next) {
            char* fuckyou = l->data;
            _Bool found = g_hash_table_contains(assy_symtable_hash, fuckyou);
            printf("  key '%s' found '%i'\n", fuckyou, found);
        }
    }
}

void assy_symtable_new(assy_symtable *in) {
    in->add = assy_symtable_add;
    in->add_variable = assy_symtable_add_variable;
    in->get = assy_symtable_get;
    in->contains = assy_symtable_contains;
    in->debug = assy_symtable_debug;
//    assy_symtable_load_predefined();
}
