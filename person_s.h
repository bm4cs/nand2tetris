#ifndef CLION_TESTDRIVE_PRINT_TYPEDEF_H
#define CLION_TESTDRIVE_PRINT_TYPEDEF_H

typedef struct person_s {
    char *name;
    char *handle;
    char **books;
    int len;
    void (*print)(struct person_s*);
};

#endif
