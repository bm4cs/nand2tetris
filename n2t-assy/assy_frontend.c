#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "assy_frontend.h"
#include "assy_translator.h"

assy_symtable assy_frontend_symtab;
assy_parser assy_frontend_parser;

void output_line(char *binary) {
    printf("%s\n", binary); //TODO: write output to file
}

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
    char symbol[100];
    memset(&symbol[0], 0, sizeof(symbol));

    char *buffer;
    int32_t variable_addr;

    while (assy_frontend_parser.read_next()) {
        switch (assy_frontend_parser.get_instruction_type()) {
//            case INSTRUCTION_TYPE_L:
//                strcpy(symbol, assy_frontend_parser.get_symbol());
//                output_line(assy_translator_get_a_instruction_bits(assy_frontend_symtab.get(symbol)));
//                break;
            case INSTRUCTION_TYPE_C:
                output_line(assy_translator_get_c_instruction_bits(
                        assy_frontend_parser.get_comp(),
                        assy_frontend_parser.get_dest(),
                        assy_frontend_parser.get_jump()));
                break;
            case INSTRUCTION_TYPE_A:
                //OK. 3 variations of addresses.
                //@SYMBOL, @NEW_VAR, @123
                //Work through these.

                strcpy(symbol, assy_frontend_parser.get_symbol());

                // case 1 its a valid symbol
                if (assy_frontend_symtab.contains(symbol)) {
                    variable_addr = assy_frontend_symtab.get(symbol);
                    output_line(assy_translator_get_a_instruction_bits(variable_addr));
                    break;
                }

                // case 2 its an alpha symbol but not in symtable; it must be a new variable
                if (isalpha(symbol[0])) {
                    variable_addr = assy_frontend_symtab.add_variable(symbol);
                    output_line(assy_translator_get_a_instruction_bits(variable_addr));
                    break;
                }

                // case 3 its just a plain old numeric address
                variable_addr = atoi(symbol);
                output_line(assy_translator_get_a_instruction_bits(variable_addr));
                break;
        }
    }
    assy_frontend_parser.reset();
}

void assy_frontend_init(char *infile, char *outfile) {
    assy_symtable_new(&assy_frontend_symtab);
    assy_parser_new(&assy_frontend_parser, infile);
}