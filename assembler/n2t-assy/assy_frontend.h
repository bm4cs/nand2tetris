#ifndef ASSY_FRONTEND_H
#define ASSY_FRONTEND_H

#include "assy_symtable.h"
#include "assy_parser.h"

assy_symtable assy_frontend_symtab;
assy_parser assy_frontend_parser;

// Constructor.
void assy_frontend_init(char *infile, char *outfile);

// Step through entire asm listing.
// If a symbol is found, store it against the very next A or C address found.
void assy_frontend_first_pass();

// With a primed symbol table, complete the assembly to binary translation.
void assy_frontend_second_pass();

#endif
