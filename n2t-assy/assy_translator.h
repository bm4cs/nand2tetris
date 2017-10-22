// The Hack assmembly language spec supports several human friendly mnemonics.
// Examples: D=D-A D=M 0;JMP
// See textbook page 109 and 110 for specification.

#ifndef ASSY_TRANSLATOR_H
#define ASSY_TRANSLATOR_H

// Translate destination mneumonic name to 3 bit representation
char* assy_translator_get_destination_bits(char *mnemonic);

// Translate compute mneumonic to 7 bit representation
char* assy_translator_get_compute_bits(char *mnemonic);

// Translate jump mneumonic name to 3 bit representation
char* assy_translator_get_jump_bits(char *mnemonic);

#endif
