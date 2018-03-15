#ifndef MSYMTABLE_H
#define MSYMTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mname {
    char         *_name;
    struct mname *_next;
};

struct list_mname {
    struct mname *_begin;
    struct mname *_end;
    int           _size;
};

typedef struct list_mname * msymtable;

msymtable msymtable_init();

msymtable msymtable_free(msymtable m);

msymtable msymtable_add_name(msymtable m, const char * name);

int msymtable_is_name_in_msymtable(msymtable m, const char * name);

#endif