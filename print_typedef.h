#ifndef CLION_TESTDRIVE_PRINT_TYPEDEF_H
#define CLION_TESTDRIVE_PRINT_TYPEDEF_H

typedef struct textlist_s {
    char *title;
    char **items;
    int len;
    void (*print)(struct textlist_s*);
};

#endif
