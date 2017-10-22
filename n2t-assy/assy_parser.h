#ifndef ASSY_PARSER_H
#define ASSY_PARSER_H

#include <stdio.h>
#include <glib.h>

extern GArray *assy_parser_input_array;

enum instruction_type { INSTRUCTION_TYPE_A, INSTRUCTION_TYPE_C, INSTRUCTION_TYPE_L };

typedef struct assy_parser {
    // Attempt to parse the next instruction.
    _Bool (*read_next)();

    // Reset the internal state of parser.
    void (*reset)();

    // Category of current instruction (A, C or L)
    enum instruction_type (*get_instruction_type)();

    // Symbol tag (if any)
    char* (*get_symbol)();

    // Destination instruction (if any)
    char* (*get_dest)();

    // Compute instruction (if any)
    char* (*get_comp)();

    // Jump instruction (if any)
    char* (*get_jump)();

    // ROM address; ignores everything other than A and C instructions
    u_int (*get_current_address)();
} assy_parser;

// Constructor. Wire up function pointers to actual implementations.
void assy_parser_new(assy_parser *in, char *filename);

#endif
