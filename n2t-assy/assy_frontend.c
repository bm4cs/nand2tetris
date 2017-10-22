#include <stdbool.h>
#include <string.h>
#include "assy_frontend.h"

assy_symtable assy_frontend_symtab;
assy_parser assy_frontend_parser;

void assy_frontend_first_pass() {
    char symbol[100];
    char *buffer;
    memset(&symbol[0], 0, sizeof(symbol));
    while (assy_frontend_parser.read_next()) {
        switch (assy_frontend_parser.get_instruction_type()) {
            case INSTRUCTION_TYPE_L:
                strcpy(symbol, assy_frontend_parser.get_symbol());
                break;
            case INSTRUCTION_TYPE_C:
            case INSTRUCTION_TYPE_A:
                if (symbol[0] != '\0') {
                    buffer = strdup(symbol);
                    assy_frontend_symtab.add(buffer, assy_frontend_parser.get_current_address());
                    memset(&symbol[0], 0, sizeof(symbol));
                }
                break;
        }
    }
    assy_frontend_parser.reset();
}

void assy_frontend_second_pass() {
}

void assy_frontend_init(char *infile, char *outfile) {
    assy_symtable_new(&assy_frontend_symtab);
    assy_parser_new(&assy_frontend_parser, infile);
    //TODO: write output
}