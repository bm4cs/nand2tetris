#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "assy_parser.h"

#define MAX_LINE_LENGTH 100

GArray *assy_parser_input_array;
u_int current_line_index = 0;
u_int current_address = 0;
_Bool first_pass = true;
char current_line_text[MAX_LINE_LENGTH];
char assy_parser_buffer_symbol[MAX_LINE_LENGTH];
char assy_parser_buffer_comp[MAX_LINE_LENGTH];
char assy_parser_buffer_dest[MAX_LINE_LENGTH];
char assy_parser_buffer_jump[MAX_LINE_LENGTH];

enum instruction_type assy_parser_get_instruction_type() {
    if (strstr(current_line_text, "@")) return INSTRUCTION_TYPE_A;
    if (strstr(current_line_text, "=")) return INSTRUCTION_TYPE_C;
    if (strstr(current_line_text, ";")) return INSTRUCTION_TYPE_C;
    return INSTRUCTION_TYPE_L;
}

_Bool assy_parser_read_next() {
    if (current_line_index == assy_parser_input_array->len - 1) return false;
    if (!first_pass) current_line_index++;
    GString *gline = g_array_index(assy_parser_input_array, GString*, current_line_index);
    char *line = gline->str;
    strcpy(current_line_text, line);
    enum instruction_type inst = assy_parser_get_instruction_type();
    if (!first_pass && (inst == INSTRUCTION_TYPE_A || inst == INSTRUCTION_TYPE_C)) current_address++;
    first_pass = false;
    return true;
}

void assy_parser_reset() {
    current_line_index = current_address = 0;
    first_pass = true;
}

char* assy_parser_get_symbol() {
    memset(&assy_parser_buffer_symbol[0], 0, sizeof(assy_parser_buffer_symbol));
    switch (assy_parser_get_instruction_type()) {
        case INSTRUCTION_TYPE_A:
            strncpy(assy_parser_buffer_symbol, current_line_text + 1, strlen(current_line_text) - 1); break;
        case INSTRUCTION_TYPE_L:
            strncpy(assy_parser_buffer_symbol, current_line_text + 1, strlen(current_line_text) - 2); break;
    }
    return assy_parser_buffer_symbol;
}

char* assy_parser_get_dest() {
    //dest=comp;jump example A=M-D
    memset(&assy_parser_buffer_dest[0], 0, sizeof(assy_parser_buffer_dest));
    char *assignment = strstr(current_line_text, "=");
    if (assignment) {
        // myspecialstring
        // ^        ^
        ulong index = assignment - current_line_text;
        strncpy(assy_parser_buffer_dest, current_line_text, index);
        return assy_parser_buffer_dest;
    }
    return NULL;
}

char* assy_parser_get_comp() {

    memset(&assy_parser_buffer_comp[0], 0, sizeof(assy_parser_buffer_comp));

    //AM=M-D comp is M-D
    char *assignment = strstr(current_line_text, "=");
    if (assignment) {
        ulong index = (assignment - current_line_text) + 1;
        ulong count = strlen(current_line_text) - index;
        strncpy(assy_parser_buffer_comp, current_line_text + index, count);
        return assy_parser_buffer_comp;
    }

    //0;JMP comp is 0
    char *semi = strstr(current_line_text, ";");
    if (semi) {
        ulong index = (semi - current_line_text);
        strncpy(assy_parser_buffer_comp, current_line_text, index);
        return assy_parser_buffer_comp;
    }
    return NULL;
}

char* assy_parser_get_jump() {
    //dest=comp;jump example 0;JMP or D;JGE
    memset(&assy_parser_buffer_jump[0], 0, sizeof(assy_parser_buffer_jump));
    char *semi = strstr(current_line_text, ";");
    if (semi) {
        ulong index = (semi - current_line_text) + 1;
        ulong count = strlen(current_line_text) - index;
        strncpy(assy_parser_buffer_jump, current_line_text + index, count);
        return assy_parser_buffer_jump;
    }
    return NULL;
}


u_int assy_parser_get_current_address() {
    return current_address;
}

void cleanstr(char *text) {
    char clean[MAX_LINE_LENGTH];
    memset(&clean[0], 0, sizeof(clean));

    int index = 0;

    for (int i=0; i<strlen(text); i++) {
        if (isspace(text[i])) continue;
        if (text[i] == '/') break;
        clean[index++] = text[i];
    }
    clean[index] = '\0';
    strcpy(text, clean);
}

void assy_parser_open_file(char *filename) {
    if (assy_parser_input_array) {
        g_array_free (assy_parser_input_array, TRUE);
    }
    assy_parser_input_array = g_array_new(false, false, sizeof(GString*));

    FILE *file = fopen(filename, "r");
    if (file) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, file)) {
            if (strstr(line, "//") && strstr(line, "//") - line == 0) continue;
            if (strlen(line) <= 1) continue;
            if (strcmp(line, "\r\n") == 0) continue;
            cleanstr(line);
            GString *gsline = g_string_new(line);
            g_array_append_val(assy_parser_input_array, gsline);
        }
        fclose(file);
    }
    else {
        printf("Error: could not open file\n");
    }
}

void assy_parser_new(assy_parser *in, char *filename) {
    in->read_next = assy_parser_read_next;
    in->get_instruction_type = assy_parser_get_instruction_type;
    in->reset = assy_parser_reset;
    in->get_comp = assy_parser_get_comp;
    in->get_dest = assy_parser_get_dest;
    in->get_jump = assy_parser_get_jump;
    in->get_symbol = assy_parser_get_symbol;
    in->get_current_address = assy_parser_get_current_address;
    assy_parser_open_file(filename);
    assy_parser_reset();
}
