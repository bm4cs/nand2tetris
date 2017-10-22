
#include <string.h>
#include "assy_translator.h"

char* assy_translator_get_destination_bits(char *mnemonic) {
    if (!mnemonic) return "000";
    if (strcmp(mnemonic, "M") == 0) return "001";
    if (strcmp(mnemonic, "D") == 0) return "010";
    if (strcmp(mnemonic, "MD") == 0) return "011";
    if (strcmp(mnemonic, "A") == 0) return "100";
    if (strcmp(mnemonic, "AM") == 0) return "101";
    if (strcmp(mnemonic, "AD") == 0) return "110";
    if (strcmp(mnemonic, "AMD") == 0) return "111";
    return -1;
}

char* assy_translator_get_compute_bits(char *mnemonic) {

    // a=0 (first bit)
    if (strcmp(mnemonic, "0") == 0) return "0101010";
    if (strcmp(mnemonic, "1") == 0) return "0111111";
    if (strcmp(mnemonic, "-1") == 0) return "0111010";
    if (strcmp(mnemonic, "D") == 0) return "0001100";
    if (strcmp(mnemonic, "A") == 0) return "0110000";
    if (strcmp(mnemonic, "!D") == 0) return "0001101";
    if (strcmp(mnemonic, "!A") == 0) return "0110001";
    if (strcmp(mnemonic, "-D") == 0) return "0001111";
    if (strcmp(mnemonic, "-A") == 0) return "0110011";
    if (strcmp(mnemonic, "D+1") == 0) return "0011111";
    if (strcmp(mnemonic, "A+1") == 0) return "0110111";
    if (strcmp(mnemonic, "D-1") == 0) return "0001110";
    if (strcmp(mnemonic, "A-1") == 0) return "0110010";
    if (strcmp(mnemonic, "D+A") == 0) return "0000010";
    if (strcmp(mnemonic, "D-A") == 0) return "0010011";
    if (strcmp(mnemonic, "A-D") == 0) return "0000111";
    if (strcmp(mnemonic, "D&A") == 0) return "0000000";
    if (strcmp(mnemonic, "D|A") == 0) return "0010101";

    // a=1 (first bit)
    if (strcmp(mnemonic, "M") == 0) return "1110000";
    if (strcmp(mnemonic, "!M") == 0) return "1110001";
    if (strcmp(mnemonic, "-M") == 0) return "1110011";
    if (strcmp(mnemonic, "M+1") == 0) return "1110111";
    if (strcmp(mnemonic, "M-1") == 0) return "1110010";
    if (strcmp(mnemonic, "D+M") == 0) return "1000010";
    if (strcmp(mnemonic, "D-M") == 0) return "1010011";
    if (strcmp(mnemonic, "M-D") == 0) return "1000111";
    if (strcmp(mnemonic, "D&M") == 0) return "1000000";
    if (strcmp(mnemonic, "D|M") == 0) return "1010101";

    return -1;
}

char* assy_translator_get_jump_bits(char *mnemonic) {
    if (!mnemonic) return "000";
    if (strcmp(mnemonic, "JGT") == 0) return "001";
    if (strcmp(mnemonic, "JEQ") == 0) return "010";
    if (strcmp(mnemonic, "JGE") == 0) return "011";
    if (strcmp(mnemonic, "JLT") == 0) return "100";
    if (strcmp(mnemonic, "JNE") == 0) return "101";
    if (strcmp(mnemonic, "JLE") == 0) return "110";
    if (strcmp(mnemonic, "JMP") == 0) return "111";
    return -1;
}