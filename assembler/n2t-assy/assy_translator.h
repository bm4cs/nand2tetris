// The Hack assmembly language spec supports several human friendly mnemonics.
// Examples: D=D-A D=M 0;JMP
// See textbook page 109 and 110 for specification.

#include <stdint.h>

#ifndef ASSY_TRANSLATOR_H
#define ASSY_TRANSLATOR_H

extern char assy_translator_address_buffer[16];
extern char assy_translator_compute_buffer[16];

// Translate destination mneumonic name to 3 bit representation
char* assy_translator_get_destination_bits(char *mnemonic);

// Translate compute mneumonic to 7 bit representation
char* assy_translator_get_compute_bits(char *mnemonic);

// Translate jump mneumonic name to 3 bit representation
char* assy_translator_get_jump_bits(char *mnemonic);

char* assy_translator_get_a_instruction_bits(int32_t address);

char* assy_translator_get_c_instruction_bits(char *comp, char *dest, char *jump);
#endif
