// The symbol table for resolving symbolic names to addresses.
// Example usage of symbols in Hack assembly:
//   @OUTPUT_D
//   0;JMP
//   (OUTPUT_FIRST)
//     @R0
//     D=M

#ifndef ASSY_SYMTABLE_H
#define ASSY_SYMTABLE_H

#include <stdint.h>
#include <glib.h>

extern GHashTable *assy_symtable_hash;
extern int32_t assy_symtable_next_available_variable_addr;

typedef struct assy_symtable {
    void (*add)(char *name, int32_t address);
    int32_t (*add_variable)(char *name);
    int32_t (*get)(char *name);
    _Bool (*contains)(char *name);
    void (*debug)();
} assy_symtable;

void assy_symtable_new(assy_symtable *in);

#endif
